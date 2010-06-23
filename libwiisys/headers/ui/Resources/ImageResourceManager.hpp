#ifndef _UI_RESOURCEMANAGER_HPP_
#define _UI_RESOURCEMANAGER_HPP_

#include <map>
#include <string>
#include <ogcsys.h>

#include "../../Object.h"
#include "ImageResource.hpp"

namespace UI
{
	namespace Resources
	{
		class ImageResourceManager : public Libwiisys::Object
		{
		public:
			static ImageResource* Get(const std::string& imagePath);
		private:
			ImageResourceManager();
			std::map<std::string, ImageResource*> _resources;
			static ImageResourceManager& Current();
		};
	}
}

#endif