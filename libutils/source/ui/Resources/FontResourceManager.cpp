#include <ui/Resources/FontResourceManager.hpp>

#include <ui/Resources/ThemeManager.hpp>
#include <fs/File.h>

#include <font_ttf.h>

using namespace UI::Resources;
using namespace std;

FontResourceManager& FontResourceManager::Current()
{
  static FontResourceManager manager;
  return manager;
}

FontResourceManager::FontResourceManager()
{
	FontResource* res = new FontResource(font_ttf, font_ttf_size);
	_resources.insert(make_pair(".", res));
}

FontResource* FontResourceManager::Get(const string& fontPath)
{
  if(fontPath == "")
	return NULL;
	
  string resourcePath = fontPath;
  if(ThemeManager::IsInitialized())
	resourcePath = ThemeManager::GetResourcePath("font/" + fontPath);

  if(!File::Exists(resourcePath))
	return Current()._resources.find(".")->second;
	
  FontResource* resource = NULL;
  map<string, FontResource*>::iterator element = Current()._resources.find(resourcePath);
  if(element != Current()._resources.end())
    return element->second;
  else
  {
	  try
	  {
		resource = new FontResource(resourcePath);
	  }
	  catch(...)
	  {
		return Current()._resources.find(".")->second;
	  }
	  
	  Current()._resources.insert(make_pair(resourcePath, resource));
	  return resource;
  }
}
