#ifndef _FILE_SYSTEM_MANAGER_EVENTS_H_
#define _FILE_SYSTEM_MANAGER_EVENTS_H_

#include <libutils/exception/Exception.h>
#include <libutils/events/EventArgs.h>
#include <libutils/Object.h>

#include <fastdelegate.h>
#include <list>

typedef struct
{
	std::string sourcePath;
	std::string destPath;
	bool isDirectory;
	bool alreadyExists;
	bool skipStep;
	bool abortProcess;
} FileSystemManagerProcessControl;

class AbortProcessException : public Exception
{
public:
	AbortProcessException();
};

class FileSystemManagerEventArgs : public EventArgs
{
private:
	FileSystemManagerProcessControl *_item;
public:
	FileSystemManagerEventArgs(FileSystemManagerProcessControl *processControl);
	FileSystemManagerProcessControl* ProcessControl();
};

class FileSystemManagerEvent
{
public:
	typedef fastdelegate::FastDelegate2<Object*, FileSystemManagerEventArgs*> DelegateType;

private:
	std::list<DelegateType> _eventList;

public:
	void operator+=(DelegateType handler);
	void operator-=(DelegateType handler);
	void Fire(Object *sender, FileSystemManagerEventArgs *args = NULL);
	void Fire(Object *sender, FileSystemManagerProcessControl *processControl);
};

#endif
