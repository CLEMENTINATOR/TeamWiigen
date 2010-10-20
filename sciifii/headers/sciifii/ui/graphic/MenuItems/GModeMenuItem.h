#ifndef _G_MODE_MENU_ITEM_H_
#define _G_MODE_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "GMenuItem.h"

class GModeMenuItem : public GMenuItem
{
  private:
	Libwui::Component::Button _btn;
	void ManageClick(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
	
  protected:
    std::string _navigationMenuId;
	std::vector<std::string> _switches;
		
  public:
    GModeMenuItem(TiXmlElement* node);
	void InitializeComponents();
};

#endif
