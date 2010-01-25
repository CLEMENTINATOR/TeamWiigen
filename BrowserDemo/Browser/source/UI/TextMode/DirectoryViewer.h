#ifndef _DIRECTORYVIEWER_H_
#define _DIRECTORYVIEWER_H_

#include "MenuBase.h"
#include "ActionMenu.h"
#include "ConfigMenu.h"
#include <vector>
#include <string>
#include <gccore.h>
#include "../../business/FileSystemManagerEvents.h"

class DirectoryViewer : public MenuBase
{
private:
	std::string currentElement;
	std::string displayedDirectory;

	ActionMenu actionMenu;
	ConfigMenu configMenu;

	void Display(const std::vector<std::string> &directories,const std::vector<std::string> &files);
	bool DoAction();
	void ExecuteFile();
	void ConfirmAction(Object *sender, FileSystemManagerEventArgs* args);

	std::vector<std::string> GetDirectories();
	std::vector<std::string> GetFiles();

public:
	DirectoryViewer();
	void Show();
};

#endif
