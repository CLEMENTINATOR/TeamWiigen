#ifndef _ADVANCEDMENU_H_
#define _ADVANCEDMENU_H_

#include "MenuBase.h"
#include <ogcsys.h>
#include <string>
#include <vector>

typedef enum
{
	amResult_Continue = 0,
	amResult_Exit = 1,
	
} AdvancedMenuResult;

class AdvancedMenu : public MenuBase
{
private:
	std::vector<std::string> actions;
	u32 menuMaxLength;
	
	u32 selectIndex;

	void Display();
public:
	AdvancedMenu();
	AdvancedMenuResult Show();
};

#endif /* ACTIONMENU_H_ */
