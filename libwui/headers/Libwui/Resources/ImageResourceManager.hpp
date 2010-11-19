#ifndef _UI_RESOURCEMANAGER_HPP_
#define _UI_RESOURCEMANAGER_HPP_

#include <map>
#include <string>
#include <ogcsys.h>

#include <libwiisys/Object.h>

#include "ImageResource.hpp"

namespace Libwui
{
  namespace Resources
  {
    class ImageResourceManager : public Libwiisys::Object
    {
      public:
        static ImageResource* Get(const std::string& imagePath);
      private:
        ImageResource defaultImage;
        ImageResourceManager();\
        static ImageResourceManager& Current();
    };
  }
}

#endif
