#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "MenuBase.h"
#include <ogcsys.h>
#include <string>
#include <vector>

typedef enum
{
	mmResult_Advanced = 0,
	mmResult_Exit = 1,
	mmResult_Nothing = 2,
	
} MainMenuResult;

class MainMenu : public MenuBase
{
private:
	std::vector<std::string> actions;
	u32 menuMaxLength;
	
	u32 selectIndex;

	void Display();
	MainMenuResult ManageConfig(u32 selection);

public:
	MainMenu();
	MainMenuResult Show();
};

#endif /* ACTIONMENU_H_ */
