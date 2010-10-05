#ifndef _MENU_ITEM_FACTORY_H_
#define _MENU_ITEM_FACTORY_H_

#include "MenuItem.h"

class MenuItemFactory : public Libwiisys::Object
{
public:
	static MenuItem* CreateItem(TiXmlElement* node);
};

#endif