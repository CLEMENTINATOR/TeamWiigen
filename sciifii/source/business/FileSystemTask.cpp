#include <iostream>
#include <sstream>
#include <string>

#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/logging/Log.h>
#include <sciifii/business/FileSystemTask.h>

using namespace std;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;
using namespace Libwiisys::Logging;


FileSystemTask::FileSystemTask(const std::string &target, FSTAction action, FSTType type, const std::string& destination, bool recursive)
    : _target(target),
    _destination(destination),
    _action(action),
    _type(type),
    _recursive(recursive)
{}

bool FileSystemTask::Prepare()
{
  if(_target == "")
    throw Exception("The target of the FileSystemTask must be provided.");

  if((_action == FSTAction_Move || _action == FSTAction_Copy) && _destination == "")
    throw Exception("A destination must be specified for copy/move actions.");

  return true;
}

void FileSystemTask::Install()
{
  if(_action == FSTAction_Copy)
  {
    if(_type == FSTType_File)
      File::Copy(_target, _destination);
    else
      Directory::Copy(_target, _destination, _recursive);
  }
  else if(_action == FSTAction_Move)
  {
    if(_type == FSTType_File)
      File::Move(_target, _destination);
    else
      Directory::Move(_target, _destination);
  }
  else if(_action == FSTAction_Delete)
  {
    if(_type == FSTType_File)
    {
      if(File::Exists(_target))
        File::Delete(_target);
    }
    else
    {
      if(Directory::Exists(_target))
        Directory::Delete(_target, _recursive);
    }
  }
}
void FileSystemTask::SendToLog()
{
  stringstream str;
  str<<"FileSystemTask("<<_target<<","<<_destination<<","<<_action<<","<<_type<<","<<_recursive<<")";
  Log::WriteLog(Log_Info,str.str());
}
