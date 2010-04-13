#include "FileSystemTask.h"

#include <libutils/fs/File.h>
#include <libutils/fs/Directory.h>
#include <libutils/exception/Exception.h>

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
		throw Exception("The target of the FileSystemTask must be provided.", -1);
		
	if(_type == FSTType_File && !File::Exists(_target))
		throw Exception("The file " + _target + " doesn't exists.", -1);
	else if(!Directory::Exists(_target))
		throw Exception("The directory " + _target + " doesn't exists.", -1);
		
	if((_action == FSTAction_Move || _action == FSTAction_Copy) && _destination == "")
		throw Exception("A destination must be specified for copy/move actions.", -1);
		
	return true;
}

void FileSystemTask::Install()
{
	if(_action == FSTAction_Copy)
	{
		if(_type == FSTType_File)
			File::Copy(_target, _destination);
		else
			Directory::Copy(_target, _destination);
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
			File::Delete(_target);
		else
			Directory::Delete(_target, _recursive);
	}
}