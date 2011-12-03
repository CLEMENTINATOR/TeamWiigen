#include <sciifii/business/FileDownloader.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <sciifii/business/common/FileManager.h>
#include <Libwiisys/logging/Log.h>

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;


FileDownloader::FileDownloader(const string &file)
    : Installer(),
    _file(file)
{}

bool FileDownloader::Prepare()
{
  OnProgress("Downloading "+_file, 0.1);
  if(!FileManager::Download(_file))
    throw Exception("Error downloading " + _file);
  OnProgress("File " + _file + " downloaded succesfully",1);
  return true;
}

void FileDownloader::Install()
{}

void FileDownloader::SendToLog()
{
  Log::WriteLog(Log_Info,"FileDownloader("+_file+")");
}
