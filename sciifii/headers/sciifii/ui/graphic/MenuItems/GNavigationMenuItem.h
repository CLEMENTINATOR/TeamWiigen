#ifndef _NAVIGATION_MENU_ITEM_H_
#define _NAVIGATION_MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include <libwui.h>
#include "IMenuItem.h"

class GNavigationMenuItem : public IMenuItem, public Libwui::Component::Button
{
protected:
	std::string _navigationMenuId;
	bool _validate;
	
public:
	GNavigationMenuItem(TiXmlElement* node);
	virtual void OnClick(Libwui::Device::PadController &c);
};

#endif
