#include <libwui/Resources/ImageResourceManager.hpp>
#include <Libwui/Resources/ThemeManager.hpp>
#include <Libwiisys/IO/File.h>
#include <notFound_png.h>

using namespace Libwui::Resources;
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
		{
			try
			{
				Device::Mount(resourcePath);
				resource = new ImageResource(resourcePath);
				Device::UnMount(resourcePath);
			}
			catch(Exception &ex)
			{
				Device::UnMount(resourcePath);
				throw;
			}
			catch(...)
			{
				Device::UnMount(resourcePath);
				throw;
			}
		}
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
