#include <sciifii/ui/graphic/MenuItems/GNavigationMenuItem.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwui::Events;

GNavigationMenuItem::GNavigationMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
  _navigationMenuId = UtilString::ToStr(node->Attribute("menuId"),"");
  _validate = UtilString::ToBool(node->Attribute("saveOptions"), true);

  _btn.Click += MakeDelegate(this, &GNavigationMenuItem::ManageClick);
}

void GNavigationMenuItem::InitializeComponents()
{
	SetSize(164,40);

	_btn.Text(_text);
  _btn.SetSize(164,40);
  _btn.DefaultImage("sd:/sciifii/default/Nav_Default.png");
  _btn.OverImage("sd:/sciifii/default/Nav_Over.png");
  _btn.ClickedImage("sd:/sciifii/default/Nav_Clicked.png");
	AddChildren(&_btn);

	Control::InitializeComponents();
}

void GNavigationMenuItem::ManageClick(Object* sender, CursorEventArgs* args)
{
  NavigateEventArgs nargs;
  nargs.ValidateCurrentMenu = _validate;
  nargs.NavigateTo = "menu";
  nargs.MenuId = _navigationMenuId;
  OnNavigate(nargs);
}
