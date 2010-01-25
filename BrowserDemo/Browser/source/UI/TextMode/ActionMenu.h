#ifndef _ACTIONMENU_H_
#define _ACTIONMENU_H_

#include "MenuBase.h"
#include <ogcsys.h>
#include <string>
#include <vector>

typedef enum
{
	amResult_Copy = 0,
	amResult_Cut = 1,
	amResult_Paste = 2,
	amResult_Delete = 3,
	amResult_Install = 4,
	amResult_Uninstall = 5,
	amResult_Cancel = 6,
} ActionMenuResult;

class ActionMenu : public MenuBase
{
private:
	std::string _filePath;
	std::vector<std::string> actions;

	u32 selectIndex;

	void Display();
	ActionMenuResult DoConfirmation();
	bool Confirm(const std::string &message);
public:
	ActionMenu();
	ActionMenuResult Show(const std::string &filePath);
};

#endif /* ACTIONMENU_H_ */
