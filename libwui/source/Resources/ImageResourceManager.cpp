#include <libwui/Resources/ImageResourceManager.hpp>
#include <Libwui/Resources/ThemeManager.hpp>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Device.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwui/Resources/ResourceManager.h>
#include <notFound_png.h>

using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;

ImageResourceManager& ImageResourceManager::Current()
{
  static ImageResourceManager manager;
  return manager;
}

ImageResourceManager::ImageResourceManager()
  : defaultImage(new ImageResource(notFound_png))
{}

ImageResource* ImageResourceManager::Get(const string& imagePath)
{
  string resourcePath = imagePath;
  if(ThemeManager::IsInitialized())
    resourcePath = ThemeManager::GetResourcePath("image/" + imagePath);

  ImageResource* resource = (ImageResource*)ResourceManager::GetResource("image." + resourcePath);
  if(resource)
	return resource;

  try
  {
    if(!File::Exists(resourcePath))
      return Current().defaultImage;

    resource = new ImageResource(resourcePath);
    ResourceManager::AddResource("image." + resourcePath, resource);
    return resource;
  }
  catch(...)
  {
	  return Current().defaultImage;
  }
}
