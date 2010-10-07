#include <Sciifii.h>

StartMenuItem::StartMenuItem(TiXmlElement* node)
  : NavigationMenuItem(node)
{
}

void StartMenuItem::ButtonPressed(u32 button)
{
	if(button & vpb_Ok)
	{
		NavigateEventArgs args;
		args.ValidateCurrentMenu = true;
		args.NavigateTo = "execution";
		args.MenuId = _navigationMenuId;
		OnNavigate(args);
	}
}
