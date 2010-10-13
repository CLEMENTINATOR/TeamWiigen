#ifndef _G_MODE_MENU_ITEM_H_
#define _G_MODE_MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include <libwui.h>
#include "IMenuItem.h"

class GModeMenuItem : public IMenuItem, public Libwui::Component::Button
{
protected:
	std::string _navigationMenuId;
	bool _validate;
	
public:
	GModeMenuItem(TiXmlElement* node);
	virtual void OnClick(Libwui::Device::PadController &c);
};

#endif
