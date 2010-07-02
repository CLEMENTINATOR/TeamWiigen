#include <malloc.h>
#include <libwiisys.h>

using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;
using namespace std;

/**
 * @brief Private constructor
 * @param fd the file descriptor
 * @param fileName the file name
 * @return An instance of NandFile
 */
NandFile::NandFile(s32 fd, const string &fileName)
{
	_fd = fd;
	_fileName = WII_ROOT_DIRECTORY ":" + fileName;

	//recup des stat
	fstats *status = (fstats*)memalign( 32, sizeof(fstats) );
	if(ISFS_GetFileStats(fd, status) < 0)
		_fileLength = 0;
	else
		_fileLength = status->file_length;

	free(status);
}

/**
 * @brief Create a NandFile
 * @param fileName The file name of the file you want to create
 * @return A reference on the new NandFile
 * @see File& File::Create(const string &fileName)
 */
NandFile& NandFile::Create(const string &fileName)
{
	s32 ret;

	if(NandFile::Exists(fileName))
		throw Exception("Can't create " + fileName+ " already exists!",-1);

	ret = ISFS_CreateFile(fileName.c_str(), 0, ISFS_OPEN_RW, ISFS_OPEN_RW, ISFS_OPEN_RW);

	if(ret < 0)
		throw Exception("Error creating file : " + fileName,ret);

	/* Open the file after creation */
	return NandFile::Open(fileName, ISFS_OPEN_WRITE);
}

/**
 * @brief Open the NandFile
 * @param fileName the NandFile you want to open
 * @param mode Could be ISFS_OPEN_WRITE etc
 * @return A reference on the opened NandFile
 * @see File& File::Open(const string &fileName, FileMode mode)
 */
NandFile& NandFile::Open(const string &fileName, u8 mode)
{
	s32 ret;

	ret = IOS_Open(fileName.c_str(), mode);
	if(ret < 0)
		throw Exception("Error opening "+fileName,ret);

	return (*new NandFile(ret, fileName));
}

/**
 * \brief Delete a file
 * \param fileName The fullpath of the file
 * \see void File::Delete(const string &fileName)
 */
void NandFile::Delete(const string &fileName)
{
	s32 ret;

	if(!NandFile::Exists(fileName))
		return;

	ret = ISFS_Delete(fileName.c_str());
	if (ret < 0)
		throw Exception("Error deleting "+fileName,ret);
}

/*!
 * \brief Check if the file exists
 * \param fileName The fullpath of the file
 * \return true if the file exists, else false if it doesn't
 * \see bool File::Exists(const string &fileName)
 */
bool NandFile::Exists(const string &fileName)
{
	u32 ownerId;
	u16 groupId;
	u8 attributes, ownerperm, groupperm, otherperm;
	return ISFS_GetAttr(fileName.c_str(), &ownerId, &groupId, &attributes, &ownerperm, &groupperm, &otherperm) == 0;
}

/**
 * @brief Write a buffer to the file
 * @param b the buffer to write
 * @see Buffer
 */
void NandFile::Write(const Buffer& b)
{
	if(IOS_Write(_fd, b.Content(), b.Length()) != (s32)b.Length())
		throw Exception("Error writing file!",-1);
}

/**
 * @brief Reads a file
 * @param b The buffer where the read data will be stocked on
 * @param len the length you want to read
 * @return the number of read chars
 */
u32 NandFile::Read(Buffer& b,u32 len)
{
	s32 nbLus = 0;
	s32 restToRead = len;

	//Vidage du buffer temporaire
	if(_rest.Length() > len)
	{
		b.Append(_rest.Content(), len);
		_rest.Truncate(len);
		return len;
	}
	else if(_rest.Length() != 0)
	{
		b.Append(_rest);
		nbLus = _rest.Length();
		restToRead -= _rest.Length();
		_rest.Clear();
	}

	//To be 32 aligned (and add more space at the end, in case of non 32 bit request)
	s32 alignedRead = 32 - (restToRead % 32) + restToRead;
	u8* tempBuffer = (u8*)memalign(32, alignedRead);
	s32 ret = IOS_Read(_fd, tempBuffer, alignedRead);

	if(ret < 0)
	{
		free(tempBuffer);
		throw Exception("Error reading file!",nbLus);
	}

	if(ret > restToRead)
	{
		b.Append(tempBuffer, restToRead);
		_rest.Append(tempBuffer + restToRead, ret - restToRead);
		nbLus += restToRead;
	}
	else
	{
		b.Append(tempBuffer, ret);
		nbLus += ret;
	}

	free(tempBuffer);
	return nbLus;
}

/**
 * @brief Close the NandFile
 */
void NandFile::Close()
{
	if(_fd)
		IOS_Close(_fd);

	_fd = 0;

	File::Close();
}

/**
 * @brief Destructor
 */
NandFile::~NandFile()
{
	Close();
}
