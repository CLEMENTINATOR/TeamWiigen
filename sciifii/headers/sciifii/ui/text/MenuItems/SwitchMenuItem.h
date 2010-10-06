#ifndef _SWITCH_MENU_ITEM_H_
#define _SWITCH_MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include "MenuItem.h"

class SwitchMenuItem : public MenuItem
{	
protected:
	bool _switchOn;
	bool _lastSwitchOn;
	std::string _switchName;
	
public:
	SwitchMenuItem(TiXmlElement* node);
	virtual void Render();
	virtual void ButtonPressed(u32 button);
	virtual void Validate();
	virtual void Cancel();
};

#endif