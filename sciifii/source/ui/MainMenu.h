#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "MenuBase.h"
#include <ogcsys.h>
#include <string>
#include <vector>

typedef enum
{
	mmResult_Hack = 0,
	mmResult_HackNoCorp = 1,
	mmResult_AdvancedHack = 2,
	mmResult_Unhack = 3,
	mmResult_Exit = 4,
	
} MainMenuResult;

class MainMenu : public MenuBase
{
private:
	std::vector<std::string> actions;
	u32 menuMaxLength;
	
	u32 selectIndex;

	void Display();
	void ManageConfig(MainMenuResult choice);
public:
	MainMenu();
	MainMenuResult Show();
};

#endif /* ACTIONMENU_H_ */
