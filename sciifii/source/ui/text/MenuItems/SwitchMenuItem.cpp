#include <iostream>
#include <sciifii/ui/text/MenuItems/SwitchMenuItem.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/String/UtilString.h>
#include <sciifii/ui/text/VirtualPad.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

SwitchMenuItem::SwitchMenuItem(TiXmlElement* node)
    : MenuItem(node),
    _switchOn(false),
    _initialSwitchOn(false),
    _lastSwitchOn(false)
{
  _switchName = UtilString::ToStr(node->Attribute("name"),"");
  if(_switchName == "")
    throw Exception("No name defined in the xml for the SwitchMenuItem");
}

void SwitchMenuItem::Render()
{
  MenuItem::Render();

  string red = "\x1b[31m";
  string green = "\x1b[32m";
  string white = "\x1b[37m";
  cout << "\t" << (_switchOn ? green + "yes" : red + "no") << white;
}

void SwitchMenuItem::ButtonPressed(u32 button)
{
  if(button & (vpb_Left | vpb_Right | vpb_Ok))
    _switchOn = !_switchOn;
}

void SwitchMenuItem::Validate()
{
  SwitchEventArgs arg;
  arg.Incremental = true;
  arg.Switches.push_back(Switch(_switchName, _switchOn));
  OnModifySwitch(arg);
  _lastSwitchOn = _switchOn;
}

void SwitchMenuItem::Cancel()
{
  _switchOn = _lastSwitchOn;
}

void SwitchMenuItem::Reset()
{
	_switchOn = _initialSwitchOn;
	_lastSwitchOn = _initialSwitchOn;
}
