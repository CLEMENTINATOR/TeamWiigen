#ifndef _UI_RESOURCE_IMAGERESOURCE_HPP_
#define _UI_RESOURCE_IMAGERESOURCE_HPP_

#include "../../Object.h"
#include <ogcsys.h>
#include <string>

namespace UI
{
  namespace Resources
  {
    class ImageResource : public Object
    {
      public:
        ImageResource(const std::string& imgPath, const u8 * defaultImage);
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
