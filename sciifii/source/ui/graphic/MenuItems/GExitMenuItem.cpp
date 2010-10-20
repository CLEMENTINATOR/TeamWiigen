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
  _btn.DefaultImage("sd:/sciifii/default/Exit_Default.png");
  _btn.OverImage("sd:/sciifii/default/Exit_Over.png");
  _btn.ClickedImage("sd:/sciifii/default/Exit_Clicked.png");
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
