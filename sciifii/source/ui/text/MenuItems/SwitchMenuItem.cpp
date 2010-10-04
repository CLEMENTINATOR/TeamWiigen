#include <iostream>
#include <Sciifii.h>

using namespace std;

SwitchMenuItem::SwitchMenuItem(TiXmlElement* node);
  : MenuItem(),
	  _switchOn(false),
		_lastSwitchOn(false)
{}

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
	OptionEventArgs arg;
	args.Incremental = true;
	args.Options.push_back(_option, _switchOn);
	OnModifyOption(args);
	_lastSwitchOn = _switchOn;
}

void SwitchMenuItem::Cancel()
{
	_switchOn = _lastSwitchOn;
}