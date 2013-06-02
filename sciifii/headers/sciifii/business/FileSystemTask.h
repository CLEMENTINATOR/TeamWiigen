#ifndef _FILE_SYSTEM_TASK_H_
#define _FILE_SYSTEM_TASK_H_

#include "common/Installer.h"

typedef enum
{
  FSTType_Folder,
  FSTType_File,
} FSTType;

typedef enum
{
  FSTAction_Copy,
  FSTAction_Delete,
  FSTAction_Move,
  FSTAction_Create
} FSTAction;

class FileSystemTask : public Installer
{
  private:
    std::string _target;
    std::string _destination;
    FSTAction _action;
    FSTType _type;
    bool _recursive;

  public:
    FileSystemTask(const std::string &target, FSTAction action, FSTType type, const std::string& destination = "", bool recursive = true);
    bool Prepare();
    void Install();
    void SendToLog();
};

#endif
