#include <sciifii/ui/graphic/MenuItems/GStartMenuItem.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwui::Events;

GStartMenuItem::GStartMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
  _validate = UtilString::ToBool(node->Attribute("saveOptions"), true);

  _btn.Click += MakeDelegate(this, &GStartMenuItem::ManageClick);
}

void GStartMenuItem::InitializeComponents()
{
  SetSize(164,40);

  _btn.Text(_text);
  _btn.SetSize(164,40);
  _btn.DefaultImage("sd:/sciifii/default/Mode_Default.png");
  _btn.OverImage("sd:/sciifii/default/Mode_Over.png");
  _btn.ClickedImage("sd:/sciifii/default/Mode_Clicked.png");
  AddChildren(&_btn);

  Control::InitializeComponents();
}

void GStartMenuItem::ManageClick(Object* sender, CursorEventArgs* args)
{
  NavigateEventArgs nargs;
  nargs.ValidateCurrentMenu = _validate;
  nargs.NavigateTo = "execution";
  OnNavigate(nargs);
}
