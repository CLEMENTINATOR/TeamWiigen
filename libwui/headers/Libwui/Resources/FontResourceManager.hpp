#ifndef _UI_FONTMANAGER_HPP_
#define _UI_FONTMANAGER_HPP_

#include <map>
#include <string>
#include <ogcsys.h>

#include <libwiisys/Object.h>

#include "FontResource.hpp"

namespace Libwui
{
  namespace Resources
  {
    class FontResourceManager : public Libwiisys::Object
    {
      public:
        static FontResource* Get(const std::string& fontPath);
      private:
        FontResource* defaultResource;
        FontResourceManager();
        static FontResourceManager& Current();
    };
  }
}

#endif
