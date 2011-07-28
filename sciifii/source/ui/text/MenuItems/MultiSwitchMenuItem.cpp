#include <iostream>
#include <sciifii/ui/text/MenuItems/MultiSwitchMenuItem.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/String/UtilString.h>
#include <sciifii/ui/text/VirtualPad.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

MultiSwitchMenuItem::MultiSwitchMenuItem(TiXmlElement* node) :
    MenuItem(node),
    _selectedIndex(0),
    _initialIndex(0),
    _lastIndex(0),
    _activated(true),
    _initialActivated(true),
    _lastActivated(true)
{
  TiXmlElement* item = node->FirstChildElement();

  while (item != NULL)
  {
    if (item->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      if (UtilString::ToStr(item->Value(), "") != "switch")
        throw Exception("Child of multiswitch isnt \"switch");

      _allowBoucle = UtilString::ToBool(item->Attribute("allowBoucle"),
                                        false);
      _allowActivation = UtilString::ToBool(item->Attribute(
                                              "allowActivation"), false);
      _activated = UtilString::ToBool(item->Attribute("activated"), true);
      _initialActivated = _activated;
      _lastActivated = _activated;

      string value = UtilString::ToStr(item->Attribute("value"), "");
      string text = UtilString::ToStr(item->Attribute("text"), "");
      if (text == "")
        throw Exception("Multiswitch child false text.");

      _multiSwitches.push_back(Switch(text, _activated, value));
    }
    item = item->NextSiblingElement();
  }
  if (_multiSwitches.empty())
    throw Exception("No children in multiswitch..");

}

void MultiSwitchMenuItem::Render()
{
  MenuItem::Render();
  string red = "\x1b[31m";
  string green = "\x1b[32m";
  string white = "\x1b[37m";
  if (_allowActivation)
  {
    if (_activated)
      cout << green;
    else
      cout << red;
  }
  cout << "\t ";
  if (!_allowBoucle)
  {
    if (_selectedIndex != 0)
      cout << " << ";
    else
      cout << "    ";
    cout << _multiSwitches[_selectedIndex].Name;

    if (_selectedIndex != _multiSwitches.size() - 1)
      cout << " >> ";
    else
      cout << "    ";
  }
  else
  {
    cout << " << " << _multiSwitches[_selectedIndex].Name << " >> ";
  }

  cout << white;
}

void MultiSwitchMenuItem::ButtonPressed(u32 button)
{
  if ((button & (vpb_Left)) && _activated)
  {
    if (_selectedIndex == 0)
    {
      if (_allowBoucle)
      {
        _selectedIndex = _multiSwitches.size() - 1;
      }
    }
    else
      _selectedIndex--;
  }
  else if ((button & (vpb_Right)) && _activated)
  {
    if (_selectedIndex == _multiSwitches.size() - 1)
    {
      if (_allowBoucle)
      {
        _selectedIndex = 0;
      }
    }
    else
      _selectedIndex++;

  }
  else if (button & (vpb_Ok))
  {
    _activated = !_activated;
  }
}

void MultiSwitchMenuItem::Validate()
{
  SwitchEventArgs arg;
  arg.Incremental = true;
  Switch s = _multiSwitches[_selectedIndex];
  s.Name = _switchName;
  s.Activated = _activated;
  arg.Switches.push_back(s);
  OnModifySwitch(arg);
  _lastIndex = _selectedIndex;
  _lastActivated = _activated;
}

void MultiSwitchMenuItem::Cancel()
{
  _selectedIndex = _lastIndex;
  _activated = _lastActivated;
}

void MultiSwitchMenuItem::Reset()
{
	_selectedIndex = _initialIndex;
	_lastIndex = _initialIndex;
	_activated = _initialActivated;
	_lastActivated = _initialActivated;
}
