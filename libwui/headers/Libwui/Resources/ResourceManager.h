#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <Libwiisys/Object.h>
#include "Resource.h"
#include <string>
#include <map>
#include <gctypes.h>

namespace Libwui
{
  namespace Resources
  {
  	  class ResourceManager : public Libwiisys::Object
  	  {
  	  private:
  		  std::map<std::string,Resource*> _resources;
  		  std::map<std::string,u32> _cacheCount;
  		  u32 _cacheLimit;

  		  ResourceManager();
  		  static ResourceManager& Current();

  	  public:
  		  static Resource* GetResource(const std::string& key);
  		  static void AddResource(const std::string& key, Resource* res);
  		  static void Clean();
  		  static void SetCacheDuration(u32 frameCount);
  	  };
  }
}

#endif
