#ifndef _MENUBASE_H_
#define _MENUBASE_H_

#include <ogcsys.h>

#define MAX_MENU_ITEM 10

class MenuBase
{
  protected:
    u32 cursorPosition;
    u32 nbItems;
    u32 skip;
    u32 skipMax;

    u32 GetCommand();
    MenuBase();
};

#endif /* MENUBASE_H_ */
