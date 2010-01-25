#include "FileSystemManagerEvents.h"

FileSystemManagerEventArgs::FileSystemManagerEventArgs(FileSystemManagerProcessControl *processControl)
  : _item(processControl)
  {}

FileSystemManagerProcessControl* FileSystemManagerEventArgs::ProcessControl()
{ return _item; }

void FileSystemManagerEvent::operator+=(DelegateType handler)
{
	_eventList.push_back(handler);
}

void FileSystemManagerEvent::operator-=(DelegateType handler)
{
	_eventList.remove(handler);
}

void FileSystemManagerEvent::Fire(Object *sender, FileSystemManagerEventArgs *args)
{
	bool toDelete = args == NULL;

	if(toDelete) args = new FileSystemManagerEventArgs(NULL);

	for(std::list<DelegateType>::iterator ite = _eventList.begin(); ite != _eventList.end(); ite++)
		(*ite)(sender, args);

	if(toDelete) delete args;
}

void FileSystemManagerEvent::Fire(Object *sender, FileSystemManagerProcessControl *processControl)
{
	FileSystemManagerEventArgs eventArgs(processControl);
	Fire(sender, &eventArgs);
}

AbortProcessException::AbortProcessException() : Exception("The process was aborted by the user", -1) {}
