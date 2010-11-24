#include <Libwui/Resources/ImageResourceManager.hpp>
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

{
	defaultImage=new ImageResource(notFound_png);
	defaultImage->isDefault=true;
}

ImageResource* ImageResourceManager::Get(const string& imagePath)
{
  string resourcePath = imagePath;
  if(ThemeManager::IsInitialized())
    resourcePath = ThemeManager::GetResourcePath("image/" + imagePath);

  ImageResource* resource = (ImageResource*)ResourceManager::GetResource(resourcePath);

  if(resource)
	return resource;

  try
  {
    if(!File::Exists(resourcePath))
      resource = Current().defaultImage;
    else
      resource = new ImageResource(resourcePath);
  }
  catch(...)
  {
	  return Current().defaultImage;
  }

  ResourceManager::AddResource(resourcePath, resource);
  return resource;
}
