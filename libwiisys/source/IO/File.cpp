#include <libwiisys.h>
#include <malloc.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys;
using namespace Libwiisys::Exceptions;

using namespace std;


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


void File::Close() {
	Device::UnMount(this->_fileName);
}


File::~File() {}


u32 File::Size() const
{
	return _fileLength;
}


Buffer File::ReadToEnd(const string& path)
{
	if(!File::Exists(path))
		throw Exception("Invalid filename : "+path,-1);

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


void File::Copy(const std::string &fileToCopy,const std::string &destFile)
{
	if(!File::Exists(fileToCopy))
		throw Exception("File to copy doesnt exist : " + fileToCopy,-1);

	if(File::Exists(destFile))
		throw Exception("File already exists : " + destFile,-1);

	Buffer b=File::ReadToEnd(fileToCopy);
	File&f=File::Create(destFile);
	f.Write(b);
	f.Close();
	delete &f;
}


void File::Move(const std::string &fileToCopy,const std::string &destFile)
{
	File::Copy(fileToCopy,destFile);
	File::Delete(fileToCopy);
}
