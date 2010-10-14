#include <sciifii/ui/text/MenuItems/ExitMenuItem.h>
#include <sciifii/ui/text/VirtualPad.h>

ExitMenuItem::ExitMenuItem(TiXmlElement* node)
    : NavigationMenuItem(node)
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
