#include <dirent.h>
#include <fat.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <libwiisys/IO/FatDirectory.h>

using namespace std;
using namespace Libwiisys::IO;

bool FatDirectory::Exists(const string &name)
{
  struct stat st;
  if (stat(name.c_str(), &st) < 0)
    return false;

  if (S_ISDIR(st.st_mode))
    return true;
  else
    return false;
}

void FatDirectory::Delete(const string &name)
{
  remove(name.c_str());
}

void FatDirectory::Create(const string &name)
{
  mkdir(name.c_str(), 0777);
}

vector<string> FatDirectory::GetFiles(const string & path)
{
  vector < string > files;

  DIR *repertoire = opendir(path.c_str());
  if (repertoire)
  {
    struct dirent *subEntry;
    while ((subEntry = readdir(repertoire)))
    {
      string subElement = path + subEntry->d_name;
      if (!Exists(subElement))
        files.push_back(subElement);
    }
    closedir(repertoire);
  }

  return files;
}

vector<string> FatDirectory::GetDirectories(const string & path)
{
  vector < string > directories;

  DIR *repertoire = opendir(path.c_str());
  if (repertoire)
  {
    struct dirent *subEntry;
    while ((subEntry = readdir(repertoire)))
    {
      //On ignore . et ..
      bool ignore = (strcmp(subEntry->d_name, ".") == 0);
      ignore = ignore || (strcmp(subEntry->d_name, "..") == 0);

      if (ignore)
        continue;

      string subElement = path + subEntry->d_name;
      if (Exists(subElement))
        directories.push_back(subElement);
    }
    closedir(repertoire);
  }

  return directories;
}

std::string FatDirectory::GetType()
{
  return "Libwiisys::IO::FatDirectory,"+Object::GetType();
}
