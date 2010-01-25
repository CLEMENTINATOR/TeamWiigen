#include "FileSystemManager.h"
#include "ConfigurationManager.h"

#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/fs/Directory.h>
#include <libutils/system/Title.h>
#include <libutils/fs/Device.h>

using namespace std;

FileSystemManager::FileSystemManager()
  : cut(false),
    clipboard()
{}

void FileSystemManager::Copy(const string &path)
{
	cut = false;
	clipboard = path;
}

bool FileSystemManager::Cut(const string &path)
{
	if(!CanCut(path))
		return false;

	cut = true;
	clipboard = path;

	return true;
}

bool FileSystemManager::Paste(const string &directory)
{
	if(!CanPaste(directory))
		return false;

	if(cut && !CanDelete(clipboard))
		return false;

	bool skip = false;

	try
	{
		if(Directory::Exists(clipboard))
		{
			if(clipboard == directory)
				skip = true;
			else if(!PasteDirectory(clipboard, directory))
				throw Exception("An error occured during the paste operation", -1);
		}
		else if(File::Exists(clipboard))
		{
			if(Path::GetParentDirectory(clipboard) == directory)
				skip = true;
			if(!PasteFile(clipboard, directory))
				throw Exception("An error occured during the paste operation", -1);
		}
		else
			return false;

		if(cut && !skip && !Delete(clipboard))
				throw Exception("An error occured while deleting the source.", -1);
		else if(cut)
			clipboard = "";
	}
	catch(AbortProcessException &exception) {}

	return true;
}

void FileSystemManager::InstallWad(const string &path)
{
	Title wad;
	wad.LoadFromWad(path, "wii:/tmp");
	wad.Install();
	wad.Clean();
}

void FileSystemManager::UninstallWad(const string &path)
{
	Title wad;
	wad.LoadFromWad(path, "wii:/tmp");
	if(wad.IsInstalled())
		wad.Uninstall();
	wad.Clean();
}

bool FileSystemManager::PasteFile(const string &sourceFile, const string &destDirectory)
{
	if(!CanPaste(destDirectory))
		return false;

	if(!File::Exists(sourceFile))
		return false;

	string destFile = Path::CleanPath(destDirectory + "/" + Path::GetFileName(sourceFile));

	//prepare beforecopiing event
	FileSystemManagerProcessControl processControl;
	processControl.sourcePath = Path::CleanPath(sourceFile);
	processControl.destPath = destFile;
	processControl.isDirectory = false;
	processControl.alreadyExists = File::Exists(destFile);
	processControl.skipStep = false;
	processControl.abortProcess = false;
	OnCopiing(&processControl);

	if(processControl.abortProcess)
		throw AbortProcessException();

	if(!processControl.skipStep)
	{
		if(File::Exists(destFile))
			File::Delete(destFile);

		File &destFileStream = File::Create(destFile);
		File &sourceFileStream = File::Open(sourceFile, FileMode_Read);
		u32 nbTotalRead = 0;
		char buffer[4096];
		try
		{
			while(nbTotalRead < sourceFileStream.Size())
			{
				u32 nbToRead = sourceFileStream.Size() - nbTotalRead;
				if(nbToRead > 4096)
					nbToRead = 4096;

				u32 nbReads = sourceFileStream.Read(buffer, nbToRead);
				destFileStream.Write(buffer,nbReads);
				nbTotalRead += nbReads;
			}
		}
		catch(...)
		{
			destFileStream.Close();
			sourceFileStream.Close();

			delete &destFileStream;
			delete &sourceFileStream;
			throw;
		}

		destFileStream.Close();
		sourceFileStream.Close();

		delete &destFileStream;
		delete &sourceFileStream;
	}

	return true;
}

bool FileSystemManager::PasteDirectory(const string &sourceDirectory, const string &destDirectory)
{
	if(!CanPaste(destDirectory))
		return false;

	if(!Directory::Exists(sourceDirectory))
		return false;

	string newDirectoryName = Path::CleanPath(destDirectory + "/" + Path::GetFileName(sourceDirectory));

	//prepare beforecopiing event
	FileSystemManagerProcessControl processControl;
	processControl.sourcePath = Path::CleanPath(sourceDirectory);
	processControl.destPath = newDirectoryName;
	processControl.isDirectory = true;
	processControl.alreadyExists = Directory::Exists(newDirectoryName);
	processControl.skipStep = false;
	processControl.abortProcess = false;
	OnCopiing(&processControl);

	if(processControl.abortProcess)
		throw AbortProcessException();

	if(!processControl.skipStep)
	{
		Directory::Create(newDirectoryName);

		vector<string> innerFiles = Directory::GetFiles(sourceDirectory);
		for(vector<string>::iterator file = innerFiles.begin(); file != innerFiles.end(); file++)
			if(!PasteFile(*file,newDirectoryName))
				throw Exception("Error copying file.",-1);

		vector<string> innerDirectories = Directory::GetDirectories(sourceDirectory);
		for(vector<string>::iterator directory = innerDirectories.begin(); directory != innerDirectories.end(); directory++)
			if(!PasteDirectory(*directory,newDirectoryName))
				throw Exception("Error copying directory.", -1);
	}

	return true;
}

FileSystemManager& FileSystemManager::Current()
{
	static FileSystemManager fsManager;
	return fsManager;
}

bool FileSystemManager::Delete(const string &path)
{
	if(!CanDelete(path))
		return false;

	if(Directory::Exists(path))
		Directory::Delete(path,true);
	else if(File::Exists(path))
		File::Delete(path);
	else
		return false;

	if(path == clipboard)
		clipboard = "";

	return true;
}

bool FileSystemManager::CanCopy(const string &path)
{
	if(Path::GetRoot(path) == path)
		return false;

	return true;
}

bool FileSystemManager::CanDelete(const string &path)
{
	if(Path::GetRoot(path) == path)
		return false;

	if(Path::GetRootName(path) == WII_ROOT_DIRECTORY
	   && ConfigurationManager::GetCurrent().IsEnSureSecurity())
		return false;

	return true;
}

bool FileSystemManager::CanPaste(const string &directory)
{
	if(clipboard == "")
		return false;

	if((Path::GetRootName(directory) == WII_ROOT_DIRECTORY)
	   && ConfigurationManager::GetCurrent().IsEnSureSecurity())
		return false;

	return Directory::Exists(directory);
}

bool FileSystemManager::CanCut(const string &path)
{
	if(Path::GetRoot(path) == path)
		return false;

	if(Path::GetRootName(path) == WII_ROOT_DIRECTORY
	   && ConfigurationManager::GetCurrent().IsEnSureSecurity())
		return false;

	return true;
}

void FileSystemManager::OnCopiing(FileSystemManagerProcessControl *processControl)
{
	BeforeCopiing.Fire(this, processControl);
}
