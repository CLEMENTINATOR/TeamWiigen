#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

NavigationMenuItem::NavigationMenuItem(TiXmlElement* node)
  : MenuItem(node)
{
	_navigationMenuId = UtilString::ToStr(node->Attribute("menuId"),"");		
	_validate = UtilString::ToBool(node->Attribute("saveOptions"), true);
}

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
