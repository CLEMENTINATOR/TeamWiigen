#ifndef _UI_FONTMANAGER_HPP_
#define _UI_FONTMANAGER_HPP_

#include <map>
#include <string>
#include <ogcsys.h>

#include <libwiisys.h>

#include "FontResource.hpp"

namespace UI
{
	namespace Resources
	{
		class FontResourceManager : public Libwiisys::Object
		{
		public:
			static FontResource* Get(const std::string& fontPath);
		private:
			FontResourceManager();
			std::map<std::string, FontResource*> _resources;
			static FontResourceManager& Current();
		};
	}
}

#endif
