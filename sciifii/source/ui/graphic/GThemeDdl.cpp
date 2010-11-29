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
		DefaultImage("drop_normal.png");
		OverImage("drop_over.png");
		UpDefaultImage("arrow_up_normal.png");
		UpClickedImage("arrow_up_clicked.png");
		UpOverImage("arrow_up_over.png");
		DownDefaultImage("arrow_down_normal.png");
		DownClickedImage("arrow_down_clicked.png");
		DownOverImage("arrow_down_over.png");
		
		if(!ThemeManager::IsInitialized() || ThemeManager::AvailableThemes().size() <= 1)
			Visible(false);
		else
		{
			//bind theme list
			vector<string> themes = ThemeManager::AvailableThemes();
			for(vector<string>::iterator theme = themes.begin(); theme != themes.end(); theme++)
			{
				AddItem(NULL, *theme);
				if(*theme == ThemeManager::CurrentTheme())
					SelectedItem(Items()[Items().size() - 1]);
			}
		}
		
		DropDownList::InitializeComponents();
}

void GThemeDdl::OnSelectedItemChanged(PadController &c)
{
	if(SelectedItem()->Text() != ThemeManager::CurrentTheme())
	{
		ThemeManager::CurrentTheme(SelectedItem()->Text());
		DropDownList::OnSelectedItemChanged(c);
	}
}