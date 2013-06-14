#include <malloc.h>
#include <ogc/isfs.h>
#include <Libwiisys/IO/Device.h>
#include <Libwiisys/IO/NandDirectory.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>

using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;
using namespace std;

void NandDirectory::Rename(const std::string &oldname, const std::string &newname)
{
    s32 ret = ISFS_Rename(oldname.c_str(),newname.c_str());
    if (ret < 0)
        throw SystemException("Couldn't rename directory : " + oldname, ret);
}


void NandDirectory::Create(const string &name)
{
  /* Create directory */
  s32 ret = ISFS_CreateDir(name.c_str(), 0, ISFS_OPEN_RW, ISFS_OPEN_RW,
                           ISFS_OPEN_RW);

  if (ret < 0)
    throw SystemException("Couldn't create directory : " + name, ret);
}

void NandDirectory::Delete(const string &name)
{
  /* Delete directory */
  s32 ret = ISFS_Delete(name.c_str());

  if (ret)
    throw SystemException("Error deleting " + name, ret);
}

bool NandDirectory::Exists(const string &name)
{
  u32 nb_files;

  if (ISFS_ReadDir(name.c_str(), NULL, &nb_files) < 0)
    return false;

  return true;
}

vector<string> NandDirectory::GetFiles(const string &name)
{
  u32 childCount, ret;
  char* childBuffer = NULL;
  vector < string > files;

  ret = ISFS_ReadDir(name.c_str(), NULL, &childCount);
  if (ret)
    throw SystemException("Can't open " + name, ret);

  if (childCount == 0)
    return files;

  childBuffer = (char*) memalign(32, (ISFS_MAXPATH + 1) * childCount);
  if (!childBuffer)
    throw Exception("Not enough memory.");

  try
  {
    ret = ISFS_ReadDir(name.c_str(), childBuffer, &childCount);
    if (ret)
      throw SystemException("Can't read " + name, ret);

    u32 charPosition = 0;
    for (u32 entryIndex = 0; entryIndex < childCount; entryIndex++)
    {
      string entryName(childBuffer + charPosition);
      // on va jusqu'a la fin du nom
      while (*(childBuffer + charPosition) != '\0')
        charPosition++;
      charPosition++;

      if (name == "/")
        entryName = name + entryName;
      else
        entryName = name + "/" + entryName;

      // Si pas directory, alors forcement file
      if (!Exists(entryName))
      {
        string realName = WII_ROOT_DIRECTORY ":" + entryName;
        files.push_back(realName);
      }
    }

    free(childBuffer);
    return files;
  }
  catch (...)
  {
    free(childBuffer);
    throw;
  }
}

vector<string> NandDirectory::GetDirectories(const string &name)
{
  u32 childCount, ret;
  char* childBuffer = NULL;
  vector < string > directories;

  ret = ISFS_ReadDir(name.c_str(), NULL, &childCount);
  if (ret)
    throw SystemException("Can't open " + name, ret);

  if (childCount == 0)
    return directories;

  childBuffer = (char*) memalign(32, (ISFS_MAXPATH + 1) * childCount);
  if (!childBuffer)
    throw Exception("Not enough memory.");

  try
  {
    ret = ISFS_ReadDir(name.c_str(), childBuffer, &childCount);
    if (ret)
      throw SystemException("Can't read " + name, ret);

    u32 charPosition = 0;
    for (u32 entryIndex = 0; entryIndex < childCount; entryIndex++)
    {
      string entryName(childBuffer + charPosition);
      // on va jusqu'a la fin du nom
      while (*(childBuffer + charPosition) != '\0')
        charPosition++;
      charPosition++;

      if (name == "/")
        entryName = "/" + entryName;
      else
        entryName = name + "/" + entryName;

      // Si directory
      if (Exists(entryName))
      {
        string realName = WII_ROOT_DIRECTORY ":" + entryName;
        directories.push_back(realName);
      }
    }

    free(childBuffer);
    return directories;
  }
  catch (...)
  {
    free(childBuffer);
    throw;
  }
}

std::string NandDirectory::GetType()
{
  return "Libwiisys::IO::NandDirectory,"+Object::GetType();
}

