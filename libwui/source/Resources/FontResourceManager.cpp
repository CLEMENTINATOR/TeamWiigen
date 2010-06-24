#include <libwui.h>

#include <libwiisys.h>
#include <font_ttf.h>

using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::IO;


FontResourceManager& FontResourceManager::Current()
{
  static FontResourceManager manager;
  return manager;
}

FontResourceManager::FontResourceManager()
{
	FontResource* res = new FontResource(font_ttf, font_ttf_size);
	_resources.insert(make_pair("", res));
}

FontResource* FontResourceManager::Get(const string& fontPath)
{
  string resourcePath = fontPath;
  if(ThemeManager::IsInitialized())
	resourcePath = ThemeManager::GetResourcePath("font/" + fontPath);

  map<string, FontResource*>::iterator element = Current()._resources.find(resourcePath);
  if(element != Current()._resources.end())
    return element->second;
	
  try
  {
	FontResource* resource = NULL;
	//si ressource n'existe pas, on met defautla la place
	if(!File::Exists(resourcePath))
	  resource = Current()._resources.find(".")->second;
	else
	  resource = new FontResource(resourcePath);
	  
	Current()._resources.insert(make_pair(resourcePath, resource));
	return resource;
  }
  catch(...)
  {
	FontResource* resource = Current()._resources.find(".")->second;
	Current()._resources.insert(make_pair(resourcePath, resource));
	return resource;
  }  
}
