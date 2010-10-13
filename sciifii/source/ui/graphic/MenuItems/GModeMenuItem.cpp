#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;

GModeMenuItem::GModeMenuItem(TiXmlElement* node)
  : IMenuItem(node)
{
	string switches = UtilString::ToStr(node->Attribute("switches"),"");
	if(switches == "")
		throw Exception("No options defined in the xml for the ModeMenuItem");
	Text(_text);
	SetSize(164,40);
	DefaultImage("sd:/sciifii/default/Mode_Default.png");
	OverImage("sd:/sciifii/default/Mode_Over.png");
	ClickedImage("sd:/sciifii/default/Mode_Clicked.png");
}

void GNavigationMenuItem::OnClick(Libwui::Device::PadController &c)
{
	SwitchEventArgs arg;
	arg.Incremental = false;
	for(vector<string>::iterator ite =  _switches.begin(); ite != _switches.end(); ite++)
		arg.Switches.push_back(Switch(*ite,true));
		
	OnModifySwitch(arg);
	StartMenuItem::ButtonPressed(button);
}
