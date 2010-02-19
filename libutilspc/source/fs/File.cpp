#include <fs/Device.h>
#include <fs/FatFile.h>
#include <fs/NandFile.h>
#include <fs/File.h>
#include <exception/Exception.h>
#include <fs/Path.h>

#include <malloc.h>

using namespace std;

/*!
 * \brief Check if the file exists
 * \param fileName The fullpath of the file
 * \return true if the file exists, else false if it doesn't
 */
bool File::Exists(const string &fileName)
{
	string path = Path::CleanPath(fileName);

	Device::Mount(path);

	bool exists = false;

	if(Device::IsFatPath(path))
		exists = FatFile::Exists(path);
	else
		exists = NandFile::Exists(Device::GetWiiPath(path));

	Device::UnMount(path);

	return exists;
}

/*!
 * \brief Open a file
 * \param fileName The fullpath of the file
 * \param mode Opening FileMode(R,W,RW)
 * \see FileMode
 * \return The opened file
 */
File& File::Open(const string &fileName, FileMode mode)
{
	string path = Path::CleanPath(fileName);

	Device::Mount(path);

	try
	{
		if(Device::IsFatPath(path))
		{
			const char *fatMode = NULL;
			switch(mode)
			{
			case FileMode_Read:
				fatMode = "rb";
				break;

			case FileMode_Write:
				fatMode = "ab";
				break;

			case FileMode_ReadWrite:
				fatMode = "rb+";
				break;
			}
			return FatFile::Open(path, fatMode);
		}
		else
		{
			string shortFile = Device::GetWiiPath(path);
			u8 nandMode = 0;
			switch(mode)
			{
			case FileMode_Read:
				nandMode = ISFS_OPEN_READ;
				break;

			case FileMode_Write:
				nandMode = ISFS_OPEN_WRITE;
				break;

			case FileMode_ReadWrite:
				nandMode = ISFS_OPEN_RW;
				break;
			}

			return NandFile::Open(shortFile, nandMode);
		}
	}
	catch(Exception &ex)
	{
		Device::UnMount(path);
		throw;
	}
}

/*!
 * \brief Create a new file
 * \param fileName The fullpath of the file
 * \return The new file (opened)
 */
 File& File::Create(const string &fileName)
{
	string path = Path::CleanPath(fileName);

	Device::Mount(path);

	try
	{
		if(Device::IsFatPath(path))
			return FatFile::Create(path);
		else
			return NandFile::Create(Device::GetWiiPath(path));
	}
	catch(Exception &ex)
	{
		Device::UnMount(path);
		throw;
	}
}

/*!
 * \brief Delete a file
 * \param fileName The fullpath of the file
 */
 void File::Delete(const string &fileName)
{
	string path = Path::CleanPath(fileName);

	Device::Mount(path);

	try
	{
		if(Device::IsFatPath(path))
			FatFile::Delete(path);
		else
			NandFile::Delete(Device::GetWiiPath(path));
	}
	catch(Exception &ex)
	{
		Device::UnMount(path);
		throw;
	}

	Device::UnMount(path);
}

/*!
 * \brief Close the opened file
 */
void File::Close()
{
	Device::UnMount(this->_fileName);
}

/*!
 * \brief Destructor
 */
File::~File() {}

/*!
 * \brief Get file length
 * \return The file length
 */
u32 File::Size() const
{
	return _fileLength;
}

/*!
 * \brief Read into a buffer
 * \param path The fullpath of the file
 * \param len This is used as output. It will contain the file length or 0 if the file doesn't exist
 * \return The address of the buffer
 */
Buffer File::ReadToEnd(const string& path)
{
	if(!File::Exists(path))
		throw Exception("Invalid filename.",-1);

	Buffer buffer;
	File &f = File::Open(path, FileMode_Read);
	
	try
	{
		f.Read(buffer, f.Size());
		f.Close();
		delete &f;
	}
	catch(Exception &ex)
	{
		f.Close();
		delete &f;
		throw;
	}

	return buffer;
}