#include <iostream>
#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

MultiSwitchMenuItem::MultiSwitchMenuItem(TiXmlElement* node) :
	MenuItem(node), _selectedIndex(0)
{

	TiXmlElement* item = node->FirstChildElement();

	while (item != NULL)
	{
		if (item->Type() != TiXmlElement::COMMENT)
		{
			if (UtilString::ToStr(item->Value(), "") != "switch")
				throw Exception("Child of multiswitch isnt \"switch");

			string value = UtilString::ToStr(item->Attribute("value"), "");

			_allowBoucle = UtilString::ToBool(item->Attribute("allowBoucle"),false);

			string text = UtilString::ToStr(item->Attribute("text"), "");
			if (text == "")
				throw Exception("Multiswitch child false text.");

			_multiSwitches.push_back(Switch(value, true, text));
		}
		item = item->NextSiblingElement();
	}
	if (_multiSwitches.empty())
		throw Exception("No children in multiswitch..");

}

void MultiSwitchMenuItem::Render()
{
	MenuItem::Render();
	cout << "\t<< " << _multiSwitches[_selectedIndex].Name << " >>";
}

void MultiSwitchMenuItem::ButtonPressed(u32 button)
{
	if (button & (vpb_Left))
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
	if (button & (vpb_Right))
	{
		if (_selectedIndex > _multiSwitches.size() - 1)
		{
			if (_allowBoucle)
			{
				_selectedIndex = 0;
			}
		}
		else
			_selectedIndex++;

	}
}

void MultiSwitchMenuItem::Validate()
{
	SwitchEventArgs arg;
	arg.Incremental = true;
	arg.Switches.push_back(_multiSwitches[_selectedIndex]);
	OnModifySwitch(arg);
}

void MultiSwitchMenuItem::Cancel()
{

}

