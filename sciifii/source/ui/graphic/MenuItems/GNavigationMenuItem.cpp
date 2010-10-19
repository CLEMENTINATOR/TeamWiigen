#include <sciifii/ui/graphic/MenuItems/GNavigationMenuItem.h>

using namespace std;
using namespace Libwiisys::String;

GNavigationMenuItem::GNavigationMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
  _navigationMenuId = UtilString::ToStr(node->Attribute("menuId"),"");
  _validate = UtilString::ToBool(node->Attribute("saveOptions"), true);
  /*Text(_text);
  SetSize(164,40);
  DefaultImage("sd:/sciifii/default/Nav_Default.png");
  OverImage("sd:/sciifii/default/Nav_Over.png");
  ClickedImage("sd:/sciifii/default/Nav_Clicked.png");*/
}

void GNavigationMenuItem::OnClick(Libwui::Device::PadController &c)
{
  NavigateEventArgs args;
  args.ValidateCurrentMenu = _validate;
  args.NavigateTo = "menu";
  args.MenuId = _navigationMenuId;
  OnNavigate(args);
}
