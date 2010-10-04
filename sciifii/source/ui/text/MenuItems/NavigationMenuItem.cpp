#include <Sciifii.h>

void NavigationMenuItem::OnNavigate(NavigateEventArgs& args)
{
	NavigateRequested(this, args);
}
	
NavigationMenuItem::NavigationMenuItem(TiXmlElement* node)
{}

void NavigationMenuItem::ButtonPressed(u32 button)
{
	if(button & vpb_Ok)
	{
		NavigateEventArgs args;
		args.ValidateCurrentMenu = _validate;
		args.NavigateTo = "menu";
		args.MenuId = _navigationMenuId;
		OnNavigate(args);
	}
}