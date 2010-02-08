#ifndef _ADVANCEDMENU_H_
#define _ADVANCEDMENU_H_

#include "MenuBase.h"
#include <ogcsys.h>
#include <string>
#include <vector>

typedef enum
{
	amResult_RestoreTrucha = 0,
	amResult_InstallCios = 1,
	amResult_InstallCorp = 2,
	amResult_Update = 3,
	amResult_Go = 4,
	amResult_Exit = 5,
	
} AdvancedMenuResult;

class AdvancedMenu : public MenuBase
{
private:
	std::vector<std::string> actions;
	u32 menuMaxLength;
	
	u32 selectIndex;

	void Display();
	void ManageConfig(AdvancedMenuResult choice);
	bool GetConfig(AdvancedMenuResult choice);
public:
	AdvancedMenu();
	AdvancedMenuResult Show();
};

#endif /* ACTIONMENU_H_ */
