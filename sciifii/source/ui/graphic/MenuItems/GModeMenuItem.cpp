#include <FastDelegate.h>
#include <sciifii/ui/graphic/MenuItems/GModeMenuItem.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwui/Events/CursorEventArgs.h>
#include <Libwui/Resources/Colors.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwui::Events;
using namespace Libwui::Resources;

GModeMenuItem::GModeMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
  string switches = UtilString::ToStr(node->Attribute("switches"),"");
  if(switches == "")
    throw Exception("No options defined in the xml for the ModeMenuItem");
	_switches = UtilString::Split(switches, '|');
	
	_btn.Click += MakeDelegate(this, &GModeMenuItem::ManageClick);
}

void GModeMenuItem::InitializeComponents()
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

void GModeMenuItem::ManageClick(Object* sender, CursorEventArgs* args)
{
  SwitchEventArgs sarg;
  sarg.Incremental = false;
  for(vector<string>::iterator ite =  _switches.begin(); ite != _switches.end(); ite++)
    sarg.Switches.push_back(Switch(*ite,true));

  OnModifySwitch(sarg);
  
	NavigateEventArgs narg;
	narg.ValidateCurrentMenu = true;
	narg.NavigateTo = "execution";
	OnNavigate(narg);
}