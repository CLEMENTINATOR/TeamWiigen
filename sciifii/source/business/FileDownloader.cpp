#include "FileDownloader.h"

#include <libutils/exception/Exception.h>

#include "common/FileManager.h"

using namespace std;

FileDownloader::FileDownloader(const string &file)
: Installer(),
  _file(file)
{}

bool FileDownloader::Prepare()
{
	if(!FileManager::Download(_file))
		throw Exception("Error downloading " + _file, -1);
		
	return true;
}

void FileDownloader::Install()
{
}

void FileDownloader::SendToLog()
{
	Log::WriteLog(Log_Info,"FileDownloader("+_file+")");
}
