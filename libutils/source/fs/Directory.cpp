#include <fs/Device.h>
#include <fs/FatDirectory.h>
#include <fs/NandDirectory.h>
#include <fs/Directory.h>
#include <exception/Exception.h>
#include <fs/File.h>
#include <fs/Path.h>

using namespace std;

/*!
 * \brief Check if the directory exists
 * \param name The fullpath of the directory
 * \return true if the directory exists, else false if it doesn't
 */
bool Directory::Exists(const string &name)
{
	string path = Path::CleanPath(name);

	Device::Mount(path);

	bool exists = false;
	if(Device::IsFatPath(path))
		exists = FatDirectory::Exists(path);
	else
		exists = NandDirectory::Exists(Device::GetWiiPath(path));

	Device::UnMount(path);

	return exists;
}

/*!
 * \brief Create a new directory
 * \param name The fullpath of the file
 */
void Directory::Create(const string &name)
{
	if(name == "")
		return;

	string path = Path::CleanPath(name);

	if(Path::GetRoot(path) == path)
		return;

	string parent = Path::GetParentDirectory(name);

	if(!Exists(parent))
		Create(parent);

	Device::Mount(path);
	if(!Exists(path))
	{
		if(Device::IsFatPath(path))
			FatDirectory::Create(path);
		else
			NandDirectory::Create(Device::GetWiiPath(name));
	}
	Device::UnMount(name);
}

/*!
 * \brief Delete a directory
 * \param name The fullpath of the directory
 * \param recursive If true, it'll delete all the subdirecories/files of the directory
 */
void Directory::Delete(const string &name, bool recursive)
{
	string path = Path::CleanPath(name);

	Device::Mount(path);

	if(Exists(path))
	{
		if(!IsEmpty(path) && !recursive)
			throw Exception("The directory is not empty.",-1);

		vector<string> files = GetFiles(path);
		vector<string> subDirectories = GetDirectories(path);

		for(vector<string>::iterator file = files.begin(); file != files.end(); file++)
			File::Delete(*file);

		for(vector<string>::iterator dir = subDirectories.begin(); dir != subDirectories.end(); dir++)
			Directory::Delete(*dir,true);

		if(Device::IsFatPath(path))
			FatDirectory::Delete(name);
		else
			NandDirectory::Delete(Device::GetWiiPath(name));
	}

	Device::UnMount(path);
}

/*!
 * \brief Get all the files of the directory
 * \param name The fullpath of the directory
 * \return An array of string containing the name of the files in the directory
 */
vector<string> Directory::GetFiles(const string &name)
{
	string path = Path::CleanPath(name);

	Device::Mount(path);
	vector<string> returnValue;

	if(!Exists(path))
	{
		Device::UnMount(path);
		throw Exception("The directory doesn't exists.",-1);
	}

	string cleanedPath = CleanPath(path);

	if(Device::IsFatPath(cleanedPath))
		returnValue = FatDirectory::GetFiles(cleanedPath);
	else
		returnValue = NandDirectory::GetFiles(Device::GetWiiPath(cleanedPath));

	Device::UnMount(path);

	return returnValue;
}

/*!
 * \brief Get all the sub-directories of the directory
 * \param name The fullpath of the directory
 * \return An array of string containing the name of the sub-directories in the directory
 */
vector<string> Directory::GetDirectories(const string &name)
{
	string path = Path::CleanPath(name);
	Device::Mount(path);
	vector<string> returnValue;

	if(!Exists(path))
	{
		Device::UnMount(path);
		throw Exception("The directory doesn't exists.",-1);
	}

	string cleanedPath = CleanPath(path);

	if(Device::IsFatPath(cleanedPath))
		returnValue = FatDirectory::GetDirectories(cleanedPath);
	else
		returnValue = NandDirectory::GetDirectories(Device::GetWiiPath(cleanedPath));

	Device::UnMount(path);

	return returnValue;
}

/*!
 * \brief "Cleans" the path
 * \param name The filePath who needs to be cleaned
 * \return The new cleaned file path
 */
string Directory::CleanPath(const string &path)
{
    if(path== (WII_ROOT_DIRECTORY ":/"))
    	return path;

    string outs = Path::CleanPath(path);
	bool needSlash = Device::IsFatPath(outs);

	if(!needSlash && outs[outs.length() -1] == '/')
		outs.erase(outs.size() - 1);
	else if(needSlash && outs[outs.length() -1] != '/')
		outs.push_back('/');

	return outs;
}

/*!
 * \brief Check if the directory is empty
 * \param name The name of the directory
 * \return true if the directory is empty, false if it isn't
 */
bool Directory::IsEmpty(const string &name)
{
	Device::Mount(name);

	if(!Exists(name))
	{
		Device::UnMount(name);
		throw Exception("The directory doesn't exists", -1);
	}

	bool empty = true;

	if(GetFiles(name).size() > 0)
		empty = false;
	else if(GetDirectories(name).size() > 0)
		empty = false;

	Device::UnMount(name);

	return empty;
}
