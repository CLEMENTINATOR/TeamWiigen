#include <malloc.h>
#include <sys/stat.h>
#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

/**
 * @brief Private constructor
 * @param fd the file descriptor
 * @param fileName the file name
 * @return An instance of FatFile
 */
FatFile::FatFile(FILE *fd, const string &fileName)
{
	this->_fd = fd;
	_fileName = fileName;


	fseek(fd, 0, SEEK_END);
	_fileLength = ftell(fd);
	fseek(fd, 0, SEEK_SET);
}

/*!
 * \brief Check if the file exists
 * \param fileName The fullpath of the file
 * \return true if the file exists, else false if it doesn't
 * \see bool File::Exists(const string &fileName)
 */
bool FatFile::Exists(const string &fileName)
{
	struct stat st;
	if(stat(fileName.c_str(), &st) < 0)
		return false;

	if(!S_ISDIR(st.st_mode))
		return true;
	else
		return false;
}

/**
 * @brief Open the FatFile
 * @param fileName the FatFile you want to open
 * @param mode Could be rw,r,w etc
 * @return A reference on the opened FatFile
 * @see File& File::Open(const string &fileName, FileMode mode)
 */
FatFile& FatFile::Open(const string &fileName, const string &mode)
{
	if(!FatFile::Exists(fileName))
		throw Exception("The file to open doesn't exists!",-1);


	FILE *fd = fopen(fileName.c_str(),mode.c_str());
	if(!fd)
		throw Exception("Error opening file : " + fileName,-1);

	return *(new FatFile(fd, fileName));
}

/**
 * @brief Close the FatFile
 */
void FatFile::Close()
{
	if(fclose(_fd) == EOF)
		throw Exception("Error closing file!",-1);

	_fd = NULL;

	File::Close();
}

/**
 * \brief Delete a file
 * \param fileName The fullpath of the file
 * \see void File::Delete(const string &fileName)
 */
void FatFile::Delete(const string &fileName)
{
	if(!FatFile::Exists(fileName))
		return;

	if(remove(fileName.c_str()))
		throw Exception("Error deleting "+fileName,-1);
}

/**
 * @brief Create a FatFile
 * @param fileName The file name of the file you want to create
 * @return A reference on the new FatFile
 * @see File& File::Create(const string &fileName)
 */
FatFile& FatFile::Create(const string &fileName)
{
	if(FatFile::Exists(fileName))
		throw Exception("Can't create " +fileName+ " already exists!",-1);

	FILE *fd = fopen(fileName.c_str(),"wb");
	if(!fd)
		throw Exception("Error creating file : " + fileName,-1);

	return *(new FatFile(fd, fileName));
}

/**
 * @brief Write a buffer to the file
 * @param b the buffer to write
 * @see Buffer
 */
void FatFile::Write(const Buffer& b)
{
	u32 pageSize = 1024;
	u32 totalToRight = b.Length();
	u32 nbWritten = 0;
	u32 nbToRight = 0;
	u32 nbWrited = 0;

	while(totalToRight > 0)
	{
		if(totalToRight < pageSize)
			nbToRight = totalToRight;
		else
			nbToRight = pageSize;

		nbWrited = fwrite((u8*)b.Content() + nbWritten, 1 , nbToRight , _fd );
		if(nbWrited == 0)
			throw Exception((char*)"Error writing file!",-1);

		nbWritten += nbWrited;
		totalToRight -= nbWrited;
	}
}

/**
 * @brief Reads a file
 * @param b The buffer where the read data will be stocked on
 * @param len the length you want to read
 * @return the number of read chars
 */
u32 FatFile::Read(Buffer& b, u32 len)
{
	void* tempBuffer = malloc(len);
	s32 nbLus = fread(tempBuffer, 1, len, _fd);

	if(nbLus < 0)
	{
		free(tempBuffer);
		throw Exception((char*)"Error reading file!",nbLus);
	}

	b.Append(tempBuffer, nbLus);
	free(tempBuffer);
	return (u32)nbLus;
}

/**
 * @brief Destructor
 */
FatFile::~FatFile()
{
	if(_fd)
		Close();
}
