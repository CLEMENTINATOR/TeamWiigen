#ifndef _NAVIGATION_MENU_ITEM_H_
#define _NAVIGATION_MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include "MenuItem.h"
#include "../Events/NavigateEvent.h"
#include "../Events/NavigateEventArgs.h"

class NavigationMenuItem : public MenuItem
{
protected:
	std::string _navigationMenuId;
	bool _validate;
	void OnNavigate(NavigateEventArgs& args);
	
public:
	NavigationMenuItem(TiXmlElement* node);
	virtual void ButtonPressed(u32 button);
	
	NavigateEvent NavigateRequested;
};

#endif