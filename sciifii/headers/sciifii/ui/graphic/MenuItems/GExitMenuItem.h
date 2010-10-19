#ifndef _G_EXIT_MENU_ITEM_H_
#define _G_EXIT_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "GMenuItem.h"

class GExitMenuItem : public GMenuItem//, public Libwui::Component::Button
{
  public:
    GExitMenuItem(TiXmlElement* node);
    virtual void OnClick(Libwui::Device::PadController &c);
};

#endif
