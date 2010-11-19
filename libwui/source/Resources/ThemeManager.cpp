#include <libwui/Resources/ThemeManager.hpp>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Path.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwui/Resources/ResourceManager.h>

using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;

ThemeManager& ThemeManager::Current()
{
  static ThemeManager t;
  return t;
}

bool ThemeManager::IsInitialized()
{
  return Current()._themeFolder.length() != 0;
}

void ThemeManager::ThemeRootFolder(const string& path)
{
  if(!Directory::Exists(path))
    throw Exception("The theme directory doesn't exists.");

  Current()._themeFolder = path;

  if(AvailableThemes().size() == 0)
  {
    Current()._themeFolder = "";
    throw Exception("The theme directory doesn't contains any theme.");
  }

  Current().CurrentTheme(AvailableThemes()[0]);
}

vector<string> ThemeManager::AvailableThemes()
{
  return Directory::GetDirectories(Current()._themeFolder);
}

void ThemeManager::CurrentTheme(const string& theme)
{
  if(Current()._themeFolder.length() == 0)
    throw Exception("The theme directory isn't specified.");

  vector<string> dirs = AvailableThemes();
  bool exists = false;
	
  for(vector<string>::iterator ite = dirs.begin(); ite != dirs.end(); ite++)
    if(*ite == theme)
    {
      exists = true;
      break;
    }

  if(!exists)
    throw Exception("The theme doesn't exists.");

  Current()._currentTheme = theme;
	ResourceManager::Clean(true);
}

string ThemeManager::GetResourcePath(const string& path)
{
  return Path::CleanPath(Current()._themeFolder + "/" + Current()._currentTheme + "/" + path);
}
