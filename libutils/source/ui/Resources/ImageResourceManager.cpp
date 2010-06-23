#include <ui/Resources/ImageResourceManager.hpp>

#include <stdlib.h>
#include <notFound_png.h>
#include <IO/Device.h>
#include <IO/File.h>
#include <ui/Resources/ThemeManager.hpp>

using namespace UI::Resources;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::IO;

ImageResourceManager& ImageResourceManager::Current()
{
  static ImageResourceManager manager;
  return manager;
}

ImageResourceManager::ImageResourceManager()
{
	ImageResource* res = new ImageResource(notFound_png);
	_resources.insert(make_pair(".", res));
}

ImageResource* ImageResourceManager::Get(const string& imagePath)
{
  string resourcePath = imagePath;
  if(ThemeManager::IsInitialized())
	resourcePath = ThemeManager::GetResourcePath("image/" + imagePath);

  map<string, ImageResource*>::iterator element = Current()._resources.find(resourcePath);
  if(element != Current()._resources.end())
    return element->second;
	
  try
  {
	ImageResource* resource = NULL;
	//si ressource n'existe pas, on met defautla la place
	if(!File::Exists(resourcePath))
	  resource = Current()._resources.find(".")->second;
	else
	  resource = new ImageResource(resourcePath);
	  
	Current()._resources.insert(make_pair(resourcePath, resource));
	return resource;
  }
  catch(...)
  {
	ImageResource* resource = Current()._resources.find(".")->second;
	Current()._resources.insert(make_pair(resourcePath, resource));
	return resource;
  }
}
