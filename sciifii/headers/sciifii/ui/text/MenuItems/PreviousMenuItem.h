#ifndef PREVIOUSMENUITEM_H_
#define PREVIOUSMENUITEM_H_

#include "NavigationMenuItem.h"
#include <gctypes.h>

class PreviousMenuItem: public NavigationMenuItem
{
  public:
    PreviousMenuItem(TiXmlElement* node);
    virtual void ButtonPressed(u32 button);
};


#endif
