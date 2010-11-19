#include <vector>
#include <string>
#include <sciifii/ui/graphic/GThemeDdl.h>
#include <Libwui/Resources/ThemeManager.hpp>

using namespace std;
using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace Libwui::Resources;

void GThemeDdl::InitializeComponents()
{
		if(!ThemeManager::IsInitialized() || ThemeManager::AvailableThemes().size() < 1)
		{
			Visible(false);
			DropDownList::InitializeComponents();
			return;
		}
		
		//bind theme list
		vector<string> themes = ThemeManager::AvailableThemes();
		for(vector<string>::iterator theme = themes.begin(); theme != themes.end(); theme++)
			AddItem(NULL, *theme);
}

void GThemeDdl::OnSelectedItemChanged(PadController &c)
{
	ThemeManager::CurrentTheme(SelectedItem()->Text());
	DropDownList::OnSelectedItemChanged(c);
}