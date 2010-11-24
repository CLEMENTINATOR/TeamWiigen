#include <Libwiisys/IO/File.h>
#include <Libwui/Resources/FontResourceManager.hpp>
#include <Libwui/Resources/ThemeManager.hpp>
#include <Libwui/Resources/ResourceManager.h>
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
	defaultResource=new FontResource(font_ttf, font_ttf_size);
	defaultResource->isDefault=true;
}

FontResource* FontResourceManager::Get(const string& fontPath)
{
  string resourcePath = fontPath;
  if(ThemeManager::IsInitialized())
    resourcePath = ThemeManager::GetResourcePath("font/" + fontPath);

  FontResource* resource = (FontResource*)ResourceManager::GetResource(resourcePath);

  if(resource)
	return resource;

  try
  {
    //si ressource n'existe pas, on met defaut a la place
    if(!File::Exists(resourcePath))
    	resource = Current().defaultResource;
    else
      resource = new FontResource(resourcePath);
  }
  catch(...)
  {
    return Current().defaultResource;
  }

  ResourceManager::AddResource(resourcePath, resource);
  return resource;
}
