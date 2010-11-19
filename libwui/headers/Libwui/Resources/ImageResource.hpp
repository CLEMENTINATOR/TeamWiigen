#ifndef _UI_RESOURCE_IMAGERESOURCE_HPP_
#define _UI_RESOURCE_IMAGERESOURCE_HPP_

#include "Resource.h"
#include <ogcsys.h>
#include <string>

namespace Libwui
{
  namespace Resources
  {
    class ImageResource : public Resource
    {
      public:
        ImageResource(const std::string& imgPath);
        ImageResource(const u8 * buffer);
        ~ImageResource();
        u8* Image();
        int Width();
        int Height();

      protected:
        u8* data; //!< Image data
        int height; //!< Height of image
        int width; //!< Width of image
    };
  }
}

#endif
