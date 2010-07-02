#ifndef _UI_RESOURCE_FONTRESOURCE_HPP_
#define _UI_RESOURCE_FONTRESOURCE_HPP_

#include <libwiisys.h>

#include "../FreeTypeGX.h"
#include <ogcsys.h>
#include <string>

namespace Libwui
{
  namespace Resources
  {
    class FontResource : public Libwiisys::Object
    {
      public:
        FontResource(const std::string& fontPath);
		FontResource(const u8* data, u32 size);
        ~FontResource();

		bool IsInitialized();
		void Initialize(bool cacheAll = false, uint8_t textureFormat = GX_TF_RGBA8, uint8_t vertexIndex = GX_VTXFMT1);
		
		FreeTypeGX* Font();
		
      protected:
		FreeTypeGX* _font;
        Libwiisys::Buffer _resource;
    };
  }
}

#endif