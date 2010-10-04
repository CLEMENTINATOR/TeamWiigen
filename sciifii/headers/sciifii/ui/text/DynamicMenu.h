#ifndef _DYNAMIC_MENU_H_
#define _DYNAMIC_MENU_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include "MenuBase.h"
#include "MenuItems/MenuItem.h"
#include "Events/NavigateEventArgs.h"

class DynamicMenu : public MenuBase
{
private:
	std::vector<MenuItem*> items;
	u32 selectIndex;

	std::string _menuId;
	NavigateEventArgs nav;
	
	void Display();
	
public:
	DynamicMenu(TiXmlElement* node);
	NavigateEventArgs Show();
};

#endif
