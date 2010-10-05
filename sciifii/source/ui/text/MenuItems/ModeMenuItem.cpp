#include <iostream>
#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

ModeMenuItem::ModeMenuItem(TiXmlElement* node)
  : StartMenuItem(node)
{
	string nodeValue = UtilString::ToStr(node->Value());
	if(nodeValue != "modeMenuItem")
		throw Exception("Can't create ModeMenuItem from the tag " + nodeValue);
		
	string switches = UtilString::ToStr(node->Attribute("switches"),"");
	if(switches == "")
		throw Exception("No options defined in the xml for the ModeMenuItem");
		
	_switches = UtilString::Split(switches, '|');
}

void ModeMenuItem::ButtonPressed(u32 button)
{
	if(button & vpb_Ok)
	{
		SwitchEventArgs arg;
		arg.Incremental = false;
		for(vector<string>::iterator ite =  _switches.begin(); ite != _switches.end(); ite++)
			arg.Switches.push_back(Switch(*ite,true));
			
		OnModifySwitch(arg);
		StartMenuItem::ButtonPressed(button);
	}
}