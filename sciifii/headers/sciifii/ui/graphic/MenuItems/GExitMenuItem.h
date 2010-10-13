#ifndef _G_EXIT_MENU_ITEM_H_
#define _G_EXIT_MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include <libwui.h>
#include "IMenuItem.h"

class GExitMenuItem : public IMenuItem, public Libwui::Component::Button
{	
public:
	GExitMenuItem(TiXmlElement* node);
	virtual void OnClick(Libwui::Device::PadController &c);
};

#endif
