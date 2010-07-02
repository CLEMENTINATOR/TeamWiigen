#include <ogcsys.h>

#include <libwiisys.h>

using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;
using namespace std;
/*!
 * \brief Get the root of the path
 * \param path A file/directory path
 * \return the root, as "wii:/" or "sd:/"
 */
string Path::GetRoot(const string &path)
{
	string rootName = GetRootName(path);

	if(rootName.length() == 0)
		return rootName;

	return rootName + ":/";
}

/*!
 * \brief Get the root name of the path
 * \param path A file/directory path
 * \return the root name, as "wii" or "sd"
 */
string Path::GetRootName(const string &path)
{
	u32 separatorPosition = path.find(':');

	if(separatorPosition == string::npos)
		return "";

	return path.substr(0,separatorPosition);
}

/*!
 * \brief Get the parent directory of the file/directory path
 * \param path A file/directory path
 * \return the access path of the parent directory
 */
string Path::GetParentDirectory(const string &path)
{
	u32 slashPosition = path.find_last_of('/');

	if(slashPosition == string::npos || path == GetRoot(path))
		return "";

	// On retire le dernier slash si besoin
	string workingRepresentation = path;
	if(slashPosition == path.length() - 1)
		workingRepresentation.erase(path.size() - 1);

	slashPosition = workingRepresentation.find_last_of('/');
	string parentDir = workingRepresentation.substr(0, slashPosition);

	//parentDir est une racine
	if(GetRootName(parentDir) + ":" == parentDir)
		return parentDir + "/";
	else
		return parentDir;
}

/*!
 * \brief Get the file name of the given path
 * \param path A file path
 * \return the file name
 */
string Path::GetFileName(const string &path)
{
	u32 slashPosition = path.find_last_of('/');

	//Si pas de / ou directory
	if(slashPosition == string::npos
			|| slashPosition == path.length() - 1)
		return "";

	return path.substr(slashPosition + 1, string::npos);
}

/*!
 * \brief Get the directory name of the given path
 * \param path A file path
 * \return the directory name
 */
string Path::GetDirectoryName(const string &path)
{
	u32 slashPosition = path.find_last_of('/');

	if(slashPosition == string::npos)
		return "";

	// On retire le dernier slash si besoin
	string workingRepresentation = path;
	if(slashPosition == path.length() - 1)
		workingRepresentation.erase(path.size() - 1);

	if(GetRootName(workingRepresentation) + ":" == workingRepresentation)
		return "";

	return workingRepresentation.substr(slashPosition + 1, string::npos);
}

/*!
 * \brief Get the file name without extension of the given path
 * \param path A file path
 * \return the file name without this extension
 * \see string Path::GetFileName(const string &path)
 */
string Path::GetFileNameWithoutExtension(const string &path)
{
	string fileName = GetFileName(path);

	if(fileName.length() == 0)
		return fileName;

	u32 pointPosition = fileName.find_last_of('.');

	if(pointPosition == string::npos)
		return fileName;

	return fileName.substr(0, pointPosition);

}

/*!
 * \brief Get the file extension
 * \param path A file path
 * \return the extension type (as dol/elf ect)
 */
string Path::GetFileExtension(const string &path)
{
	string fileName = GetFileName(path);

	u32 pointPosition = fileName.find_last_of('.');

	//Si pas de / ou directory
	if(pointPosition == string::npos
			|| pointPosition == path.length() - 1)
		return "";

	return fileName.substr(pointPosition + 1, string::npos);
}

/*!
 * \brief Cleans the given path
 * \param path A file path
 * \return the new cleaned path
 */
string Path::CleanPath(const string &path)
{
	u32 pos = 0;
	string work = path;
	while((pos=work.find("//")) != string::npos)
	{
		work.replace(pos, 2, "/",1);
	}
	return work;
}
