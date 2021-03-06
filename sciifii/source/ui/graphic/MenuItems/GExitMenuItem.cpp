#include <sciifii/ui/graphic/MenuItems/GExitMenuItem.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwui::Events;

GExitMenuItem::GExitMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
  _btn.Click += MakeDelegate(this, &GExitMenuItem::ManageClick);
}

void GExitMenuItem::InitializeComponents()
{
  SetSize(164,40);
  _btn.Text(_text);
  _btn.SetSize(164,40);
  _btn.DefaultImage("Exit_Default.png");
  _btn.OverImage("Exit_Over.png");
  _btn.ClickedImage("Exit_Clicked.png");
	_btn.SetFont("ExitMenuItem.ttf");
  AddChildren(&_btn);
  Control::InitializeComponents();
}

void GExitMenuItem::ManageClick(Object* sender, CursorEventArgs* args)
{
  NavigateEventArgs nargs;
  nargs.ValidateCurrentMenu = false;
  nargs.NavigateTo = "loader";
  nargs.MenuId = "";
  OnNavigate(nargs);
}
