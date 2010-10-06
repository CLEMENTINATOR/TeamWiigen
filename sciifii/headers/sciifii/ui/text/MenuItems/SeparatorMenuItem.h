#ifndef _SEPERATOR_MENU_ITEM_H_
#define _SEPERATOR_MENU_ITEM_H_

#include "MenuItem.h"

class SeparatorMenuItem : public MenuItem
{
private:
  char _separator;
  
public:
  SeparatorMenuItem(TiXmlElement* node);
  virtual void Render();
};

#endif