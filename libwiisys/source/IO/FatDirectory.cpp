#include <dirent.h>
#include <fat.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

/**
 * \brief Check if the directory exists
 *  \param name The absolute path of the directory
 * \return true if directory exists, else false
 * \see void Directory::Exists(const string &name)
 */
bool FatDirectory::Exists(const string &name)
{
	struct stat st;
	if(stat(name.c_str(), &st) < 0)
		return false;

	if(S_ISDIR(st.st_mode))
		return true;
	else
		return false;
}
/**
 * \brief Delete the given directory
 *  \param name The absolute path of the directory
 *  \see void Directory::Delete(const string &name)
 */
void FatDirectory::Delete(const string &name)
{
	remove(name.c_str());
}

/**
 *\brief Create the given directory
 *\param name The absolute path of the directory
 *\see void Directory::Create(const string &name)
 */
void FatDirectory::Create(const string &name)
{
	mkdir(name.c_str(),0777);
}

/*!
 * \brief Get all the files of the directory
 * \param name The full path of the directory
 * \return An array of string containing the name of the files in the directory
 * \see vector<string> Directory::GetFiles(const string &name)
 */
vector<string> FatDirectory::GetFiles (const string & path)
{
	vector<string> files;

	DIR *repertoire = opendir(path.c_str());
	if(repertoire)
	{
		struct dirent *subEntry;
		while((subEntry = readdir(repertoire)))
		{
			string subElement = path + subEntry->d_name;
			if(!Exists(subElement))
				files.push_back(subElement);
		}
		closedir(repertoire);
	}

	return files;
}

/*!
 * \brief Get all the sub-directories of the directory
 * \param name The full path of the directory
 * \return An array(vector) of string containing the name of the sub-directories in the directory
 * \see vector<string> Directory::GetDirectories(const string & path)
 */
vector<string> FatDirectory::GetDirectories(const string & path)
{
	vector<string> directories;

	DIR *repertoire = opendir(path.c_str());
	if(repertoire)
	{
		struct dirent *subEntry;
		while((subEntry = readdir(repertoire)))
		{
			//On ignore . et ..
			bool ignore = (strcmp(subEntry->d_name, ".") == 0);
			ignore = ignore || (strcmp(subEntry->d_name, "..") == 0);

			if(ignore)
				continue;

			string subElement = path + subEntry->d_name;
			if(Exists(subElement))
				directories.push_back(subElement);
		}
		closedir(repertoire);
	}

	return directories;
}
