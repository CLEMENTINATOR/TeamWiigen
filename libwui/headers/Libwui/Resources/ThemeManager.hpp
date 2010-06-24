#ifndef _UI_RESOURCES_THEME_MANAGER_H_
#define _UI_RESOURCES_THEME_MANAGER_H_

#include <libwiisys.h>

#include <string>
#include <vector>

namespace Libwui
{
	namespace Resources
	{
		class ThemeManager : public Libwiisys::Object
		{
		private:
			std::string _currentTheme;
			std::string _themeFolder;
			
			static ThemeManager& Current();
		public:
			static bool IsInitialized();
			static void ThemeRootFolder(const std::string& path);
			static std::vector<std::string> AvailableThemes();
			static void CurrentTheme(const std::string& theme);
			static std::string GetResourcePath(const std::string& path);
		};
	}
}

#endif
