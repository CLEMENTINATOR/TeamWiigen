#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Device.h>
#include <Libwiisys/IO/Path.h>
#include <Libwiisys/IO/FatDirectory.h>
#include <Libwiisys/IO/NandDirectory.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

bool Directory::Exists(const string &name)
{
  string path = CleanPath(name);

  Device::Mount(path);

  bool exists = false;
  if (Device::IsFatPath(path))
    exists = FatDirectory::Exists(path);
  else
    exists = NandDirectory::Exists(Device::GetWiiPath(path));

  Device::UnMount(path);

  return exists;
}

void Directory::Rename(const std::string &oldname, const std::string &newname)
{
  string path = CleanPath(oldname);
  string newPath = CleanPath(newname);
  
  Device::Mount(path);
  Device::Mount(newPath); //if different paths
  
    if (!Exists(path))
        throw Exception(path + " doesn't exists.");
 
    if (Device::IsFatPath(path))
        FatDirectory::Rename(path,newPath);
    else
        NandDirectory::Rename(Device::GetWiiPath(path),Device::GetWiiPath(newPath));
  
  Device::UnMount(path);
  Device::UnMount(newPath);
}


void Directory::Create(const string &name)
{
  if (name == "")
    return;
    
  if (Path::GetRoot(name) == name)
    return;
    
  string path = CleanPath(name); 
  
  string parent = Path::GetParentDirectory(path);

  if (!Exists(parent))
    Create(parent);

  Device::Mount(path);
  if (!Exists(path))
  {
    if (Device::IsFatPath(path))
      FatDirectory::Create(path);
    else
      NandDirectory::Create(Device::GetWiiPath(path));
  }
  Device::UnMount(path);
}

void Directory::Delete(const string &name, bool recursive)
{
  string path = CleanPath(name);
  Device::Mount(path);

  if (Exists(path))
  {
    if (!IsEmpty(path) && !recursive)
      throw Exception(path + " is not empty.");

    vector < string > files = GetFiles(path);
    vector < string > subDirectories = GetDirectories(path);

    for (vector<string>::iterator file = files.begin(); file != files.end(); file++)
    {
      File::Delete(*file);
    }

    for (vector<string>::iterator dir = subDirectories.begin(); dir
         != subDirectories.end(); dir++)
      Directory::Delete(*dir, true);

    if (Device::IsFatPath(path))
      FatDirectory::Delete(path);
    else
      NandDirectory::Delete(Device::GetWiiPath(path));
  }

  Device::UnMount(path);
}

vector<string> Directory::GetFiles(const string &name)
{
  string path = CleanPath(name);

  Device::Mount(path);
  vector < string > returnValue;

  if (!Exists(path))
  {
    Device::UnMount(path);
    throw Exception(path + " doesn't exists.");
  }

  if (Device::IsFatPath(path))
    returnValue = FatDirectory::GetFiles(path + "/");
  else
    returnValue = NandDirectory::GetFiles(Device::GetWiiPath(path));

  Device::UnMount(path);

  return returnValue;
}

vector<string> Directory::GetDirectories(const string &name)
{
  string path = CleanPath(name);
  Device::Mount(path);
  vector < string > returnValue;

  if (!Exists(path))
  {
    Device::UnMount(path);
    throw Exception(path + " doesn't exists.");
  }

  if (Device::IsFatPath(path))
    returnValue = FatDirectory::GetDirectories(path + "/");
  else
    returnValue = NandDirectory::GetDirectories(Device::GetWiiPath(
                    path));

  Device::UnMount(path);

  return returnValue;
}

string Directory::CleanPath(const string &path)
{
  if (path == Path::GetRoot(path))
    return path;

  string outs = Path::CleanPath(path);

  if (outs[outs.length() - 1] == '/')
    outs.erase(outs.size() - 1);

  return outs;
}

bool Directory::IsEmpty(const string &name)
{
  string path = Directory::CleanPath(name);
  Device::Mount(path);

  if (!Exists(path))
  {
    Device::UnMount(path);
    throw Exception(path + " doesn't exists.");
  }

  bool empty = true;

  if (GetFiles(path).size() > 0)
    empty = false;
  else if (GetDirectories(path).size() > 0)
    empty = false;

  Device::UnMount(path);

  return empty;
}

void Directory::Copy(const string &name, const string &dest, bool recursive)
{
  string path = Directory::CleanPath(name);

  string cdest = "";

  //create the directory?
  if (path.c_str()[path.size() - 1] == '/' && recursive)
  {
    cdest = Directory::CleanPath(dest + "/" + Path::GetDirectoryName(path));
  }
  else
  {
    cdest = Directory::CleanPath(dest);
  }
   
  Device::Mount(path);
  Device::Mount(cdest);

  if (Exists(path))
  {
    if (!Exists(cdest))
    {
      Create(cdest);
    }

    vector < string > files = GetFiles(path);
    vector < string > subDirectories = GetDirectories(path);

    for (vector<string>::iterator file = files.begin(); file != files.end(); file++)
    {
      string destination = cdest + "/" + Path::GetFileName(*file);
      File::Copy(*file, destination);
    }

    if (recursive)
    {
      for (vector<string>::iterator dir = subDirectories.begin(); dir
           != subDirectories.end(); dir++)
      {
        string directoryName = Path::GetDirectoryName(*dir);
        string destination = cdest + "/" + directoryName;
        Directory::Copy(*dir, destination,recursive);
      }
    }
  }

  Device::UnMount(path);
  Device::Mount(cdest);
}

void Directory::Move(const string &name, const string &dest)
{
  Directory::Copy(name, dest, true);
  Directory::Delete(name, true);
}

std::string Directory::GetType()
{
  return "Libwiisys::IO::Directory,"+Object::GetType();
}
