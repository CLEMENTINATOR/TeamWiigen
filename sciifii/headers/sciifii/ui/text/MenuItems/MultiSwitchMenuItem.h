#ifndef _MULTISWITCH_MENU_ITEM_H_
#define _MULTISWITCH_MENU_ITEM_H_

#include <string>
#include <vector>
#include <libwiisys.h>
#include "MenuItem.h"

class MultiSwitchMenuItem : public MenuItem
{
protected:

	std::vector<Switch> _multiSwitches;
	u32 _selectedIndex;
	u32 _lastIndex;
	bool _allowBoucle;
	bool _allowActivation;
	bool _activated;
	bool _lastActivated;
	std::string _switchName;

public:
	MultiSwitchMenuItem(TiXmlElement* node);
	virtual void Render();
	virtual void ButtonPressed(u32 button);
	virtual void Validate();
	virtual void Cancel();
};

#endif
