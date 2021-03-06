#include <sciifii/ui/graphic/MenuItems/GSwitchMenuItem.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/String/UtilString.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

GSwitchMenuItem::GSwitchMenuItem(TiXmlElement* node)
    : GMenuItem(node),
      _initialSwitchOn(false),
    _lastSwitchOn(false)
{
  _switchName = UtilString::ToStr(node->Attribute("name"),"");
  if(_switchName == "")
    throw Exception("No name defined in the xml for the GSwitchMenuItem");
}

void GSwitchMenuItem::InitializeComponents()
{
	SetSize(164,40);
	_cbx.SetSize(164,40);
	_cbx.Checked(false);
	_cbx.CheckedImage("enable_button.png");
	_cbx.DefaultImage("disable_button.png");
	_cbx.Text(_text);
	_cbx.SetFont("SwitchMenuItem.ttf");
	AddChildren(&_cbx);
	
	GMenuItem::InitializeComponents();
}

void GSwitchMenuItem::Validate()
{
  SwitchEventArgs arg;
  arg.Incremental = true;
  arg.Switches.push_back(Switch(_switchName, _cbx.Checked()));
  OnModifySwitch(arg);
  _lastSwitchOn = _cbx.Checked();
}

void GSwitchMenuItem::Cancel()
{
  _cbx.Checked(_lastSwitchOn);
}

void GSwitchMenuItem::Reset()
{
	_cbx.Checked(_initialSwitchOn);
	_lastSwitchOn = _initialSwitchOn;
}
