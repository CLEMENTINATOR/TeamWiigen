#ifndef _SEPERATOR_MENU_ITEM_H_
#define _SEPERATOR_MENU_ITEM_H_

#include <string>
#include "MenuItem.h"

class SeparatorMenuItem : public MenuItem
{
private:
  std::string _separator;
  
public:
  SeparatorMenuItem(TiXmlElement* node);
  virtual void Render();
};

#endif