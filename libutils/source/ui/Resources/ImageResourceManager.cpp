#include <ui/Resources/ImageResourceManager.hpp>

#include <stdlib.h>
#include <notFound_png.h>
#include <fs/Device.h>
#include <fs/File.h>
#include <ui/Resources/ThemeManager.hpp>

#include <logging/Log.h>

using namespace UI::Resources;
using namespace std;

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
  if(imagePath.length() == 0)
  {
	/*Log::Write(Log_Warning, "ImageResourceManager::Get", imagePath, -1);*/
	return Current()._resources.find(".")->second;
  }

  string resourcePath = imagePath;
  if(ThemeManager::IsInitialized())
	resourcePath = ThemeManager::GetResourcePath("image/" + imagePath);

  if(!File::Exists(resourcePath))
  {
	/*Log::Write(Log_Warning, "ImageResourceManager::Get", imagePath, -1);*/
	return Current()._resources.find(".")->second;
  }

  ImageResource* resource = NULL;
  map<string, ImageResource*>::iterator element = Current()._resources.find(resourcePath);
  if(element != Current()._resources.end())
    return element->second;
  else
  {
	  try
	  {
		Device::Mount(resourcePath);
		resource = new ImageResource(resourcePath);
		Device::UnMount(resourcePath);
	  }
	  catch(...)
	  {
	/*	Log::Write(Log_Warning, "ImageResourceManager::Get", imagePath, -1);*/
		return Current()._resources.find(".")->second;
	  }

	  Current()._resources.insert(make_pair(resourcePath, resource));
	  return resource;
  }
}
