#ifndef _G_SEPARATOR_MENU_ITEM_H_
#define _G_SEPARATOR_MENU_ITEM_H__

#include <Libwiisys/Serialization/Xml.h>
#include "GMenuItem.h"

class GSeparatorMenuItem : public GMenuItem
{
  public:
    GSeparatorMenuItem(TiXmlElement* node);
    void InitializeComponents();
};

#endif
