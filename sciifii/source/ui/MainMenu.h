#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "MenuBase.h"
#include <ogcsys.h>
#include <string>
#include <vector>

typedef enum
{
	mmResult_RestoreTrucha = 0,
	mmResult_InstallCios = 1,
	mmResult_InstallCorp = 2,
	mmResult_Update = 3,
	mmResult_Go = 4,
	mmResult_Uninstall = 5,
	mmResult_Exit = 6,
	
} MainMenuResult;

class MainMenu : public MenuBase
{
private:
	std::vector<std::string> actions;
	u32 menuMaxLength;
	
	u32 selectIndex;

	void Display();
	void ManageConfig(MainMenuResult choice);
	bool GetConfig(MainMenuResult choice);
public:
	MainMenu();
	MainMenuResult Show();
};

#endif /* ACTIONMENU_H_ */
