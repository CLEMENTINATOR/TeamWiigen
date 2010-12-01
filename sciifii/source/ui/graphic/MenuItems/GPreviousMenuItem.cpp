#include <Libwiisys/String/UtilString.h>
#include <sciifii/ui/graphic/MenuItems/GPreviousMenuItem.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwui::Events;

GPreviousMenuItem::GPreviousMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
  _validate = UtilString::ToBool(node->Attribute("saveOptions"), true);

  _btn.Click += MakeDelegate(this, &GPreviousMenuItem::ManageClick);
}

void GPreviousMenuItem::InitializeComponents()
{
  SetSize(164,40);

  _btn.Text(_text);
  _btn.SetSize(164,40);
  _btn.DefaultImage("Mode_Default.png");
  _btn.OverImage("Mode_Over.png");
  _btn.ClickedImage("Mode_Clicked.png");
	_btn.SetFont("PreviousMenuItem.ttf");
  AddChildren(&_btn);

  Control::InitializeComponents();
}

void GPreviousMenuItem::ManageClick(Object* sender, CursorEventArgs* args)
{
  NavigateEventArgs nargs;
  nargs.ValidateCurrentMenu = _validate;
  nargs.NavigateTo = "menu";
  nargs.MenuId = "..";
  OnNavigate(nargs);
}
