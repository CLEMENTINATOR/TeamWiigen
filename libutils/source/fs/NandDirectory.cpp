#include <malloc.h>

#include <exception/Exception.h>
#include <fs/NandDirectory.h>
#include <fs/Device.h>

using namespace std;

void NandDirectory::Create(const string &name)
{
	/* Create directory */
	s32 ret = ISFS_CreateDir(name.c_str(), 0, ISFS_OPEN_RW, ISFS_OPEN_RW, ISFS_OPEN_RW);

	if(ret < 0)
		throw Exception("couldn't create directory!",ret);
}

void NandDirectory::Delete(const string &name)
{
	/* Delete directory */
	s32 ret = ISFS_Delete(name.c_str());

	if(ret)
		throw Exception("Error deleting file",ret);
}

bool NandDirectory::Exists(const string &name)
{
	u32  nb_files;

	if (ISFS_ReadDir(name.c_str(), NULL, &nb_files) < 0)
		return false;

	return true;
}

vector<string> NandDirectory::GetFiles(const string &name)
{
	u32 childCount, ret;
	char* childBuffer = NULL;
	vector<string> files;

	ret = ISFS_ReadDir(name.c_str(), NULL, &childCount);
	if(ret)
		throw Exception("Can't open the directory.", ret);

    if(childCount==0) return files;

	childBuffer = (char*)memalign(32, (ISFS_MAXPATH + 1) * childCount);
	if(!childBuffer)
		throw Exception("Not enough memory.",-1);

	try
	{
		ret = ISFS_ReadDir(name.c_str(), childBuffer, &childCount);
		if(ret)
			throw Exception("Can't read the directory.", ret);

		u32 charPosition = 0;
		for(u32 entryIndex = 0; entryIndex < childCount; entryIndex++)
		{
			string entryName(childBuffer + charPosition);
			// on va jusqu'a la fin du nom
			while(*(childBuffer + charPosition) != '\0')
			  charPosition++;
			charPosition++;


			if(name == "/")
				entryName = name + entryName;
			else
				entryName = name + "/" + entryName;

			// Si pas directory, alors forcement file
                if(!Exists(entryName))
                {
			  string realName = WII_ROOT_DIRECTORY ":" + entryName;
			  files.push_back(realName);
                }
		}

		free(childBuffer);
		return files;
	}
	catch(...)
	{
		free(childBuffer);
		throw;
	}
}
vector<string> NandDirectory::GetDirectories(const string &name)
{
	u32 childCount, ret;
	char* childBuffer = NULL;
	vector<string> directories;

	ret = ISFS_ReadDir(name.c_str(), NULL, &childCount);
	if(ret)
		throw Exception("Can't open the directory.", ret);


    if(childCount==0) return directories;

	childBuffer = (char*)memalign(32, (ISFS_MAXPATH + 1) * childCount);
	if(!childBuffer)
		throw Exception("Not enough memory.",-1);

	try
	{
		ret = ISFS_ReadDir(name.c_str(), childBuffer, &childCount);
		if(ret)
			throw Exception("Can't read the directory.", ret);

		u32 charPosition = 0;
		for(u32 entryIndex = 0; entryIndex < childCount; entryIndex++)
		{
			string entryName(childBuffer + charPosition);
			// on va jusqu'a la fin du nom
			while(*(childBuffer + charPosition) != '\0')
			  charPosition++;
			charPosition++;


			if(name == "/")
				entryName = "/" + entryName;
			else
				entryName = name + "/" + entryName;

			// Si directory
if(Exists(entryName))
                {
			  string realName = WII_ROOT_DIRECTORY ":" + entryName;
			  directories.push_back(realName);
                }
		}

		free(childBuffer);
		return directories;
	}
	catch(...)
	{
		free(childBuffer);
		throw;
	}
}
