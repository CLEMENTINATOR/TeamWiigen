#ifndef _UI_RESOURCE_FONTRESOURCE_HPP_
#define _UI_RESOURCE_FONTRESOURCE_HPP_

#include <Libwiisys/Buffer.h>
#include <FreeTypeGX.h>
#include "Resource.h"
#include <ogcsys.h>
#include <string>
#include <map>

namespace Libwui
{
  namespace Resources
  {
    class FontResource : public Resource
    {
      public:
        FontResource(const std::string& fontPath);
        FontResource(const u8* data, u32 size);
        ~FontResource();

        bool IsInitialized(s32 size);
        void Initialize(s32 size, bool cacheAll = false, uint8_t textureFormat = GX_TF_RGBA8, uint8_t vertexIndex = GX_VTXFMT1);

		void Clean();
		
        FreeTypeGX* Font(s32 size);

      protected:
        std::map<s32,FreeTypeGX*> _fonts;
		std::map<s32,u32> _cacheCount;
        Libwiisys::Buffer _resource;
    };
  }
}

#endif
