#include <sciifii/ui/graphic/MenuItems/GModeMenuItem.h>
#include <Libwiisys/Exceptions/Exception.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

GModeMenuItem::GModeMenuItem(TiXmlElement* node)
    : IMenuItem(node)
{
  string switches = UtilString::ToStr(node->Attribute("switches"),"");
  if(switches == "")
    throw Exception("No options defined in the xml for the ModeMenuItem");
	_switches = UtilString::Split(switches, '|');
	
  Text(_text);
  SetSize(164,40);
  DefaultImage("sd:/sciifii/default/Mode_Default.png");
  OverImage("sd:/sciifii/default/Mode_Over.png");
  ClickedImage("sd:/sciifii/default/Mode_Clicked.png");
}

void GModeMenuItem::OnClick(Libwui::Device::PadController &c)
{
  SwitchEventArgs arg;
  arg.Incremental = false;
  for(vector<string>::iterator ite =  _switches.begin(); ite != _switches.end(); ite++)
    arg.Switches.push_back(Switch(*ite,true));

  OnModifySwitch(arg);
  
	NavigateEventArgs args;
	args.ValidateCurrentMenu = true;
	args.NavigateTo = "execution";
	OnNavigate(args);
}
