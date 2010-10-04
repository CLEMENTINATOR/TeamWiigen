#include <Sciifii.h>

ExitMenuItem::ExitMenuItem(TiXmlElement* node)
{}

void ExitMenuItem::ButtonPressed(u32 button)
{
	if(button & vpb_Ok)
	{
		NavigateEventArgs args;
		args.ValidateCurrentMenu = false;
		args.NavigateTo = "loader";
		args.MenuId = _navigationMenuId;
		OnNavigate(args);
	}
}