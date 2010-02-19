#include <ui/Resources/ThemeManager.hpp>
#include <exception/Exception.h>
#include <fs/Directory.h>
#include <fs/Path.h>

using namespace UI::Resources;
using namespace std;

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
		throw Exception("The theme directory doesn't exists.", -1);
		
	Current()._themeFolder = path;
	
	vector<string> dirs = Directory::GetDirectories(Current()._themeFolder);
	
	if(dirs.size() == 0)
	{
		Current()._themeFolder = "";
		throw Exception("The theme directory doesn't contains any theme.", -1);
	}
	
	CurrentTheme(dirs[0]);
}

vector<string> ThemeManager::AvailableThemes()
{
	return Directory::GetDirectories(Current()._themeFolder);
}

void ThemeManager::CurrentTheme(const string& theme)
{
	if(Current()._themeFolder.length() == 0)
		throw Exception("The theme directory isn't specified.", -1);
		
	vector<string> dirs = Directory::GetDirectories(Current()._themeFolder);
	bool exists = false;
	for(vector<string>::iterator ite = dirs.begin(); ite != dirs.end(); ite++)
		if(*ite == theme)
		{
			exists = true;
			break;
		}
	
	if(!exists)
		throw Exception("The theme doesn't exists.", -1);
		
	Current()._currentTheme = theme;
}

string ThemeManager::GetResourcePath(const string& path)
{
	return Path::CleanPath(Current()._themeFolder + "/" + Current()._currentTheme + "/" + path);
}
