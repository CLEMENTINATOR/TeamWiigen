#include <ui/Resources/ImageResourceManager.hpp>

#include <stdlib.h>
#include <notFound_png.h>
#include <fs/Device.h>
#include <ui/Resources/ThemeManager.hpp>

using namespace UI::Resources;
using namespace std;

ImageResourceManager& ImageResourceManager::Current()
{
  static ImageResourceManager manager;
  return manager;
}

ImageResource* ImageResourceManager::Get(const string& imagePath)
{
  if(imagePath.length() == 0)
	return NULL;
	
  string resourcePath = imagePath;
  if(ThemeManager::IsInitialized())
	resourcePath = ThemeManager::GetResourcePath("image/" + imagePath);
	
  ImageResource* resource = NULL;
  map<string, ImageResource*>::iterator element = Current()._resources.find(resourcePath);
  if(element != Current()._resources.end())
    return element->second;
  else
  {
	  //for the moement i will only use precompiled images
	  try
	  {
		Device::Mount(resourcePath);
		resource = new ImageResource(resourcePath, notFound_png);
		Device::UnMount(resourcePath);
	  }
	  catch(...)
	  {
		return NULL;
	  }
	  
	  Current()._resources.insert(make_pair(resourcePath, resource));
	  return resource;
  }
}
