#ifndef _WAD_INSTALLER_H_
#define _WAD_INSTALLER_H_

#include "common/Installer.h"

typedef enum
{
	wa_Install,
	wa_Uninstall,
} WadAction;

class Wad : public Installer
{
private:
	std::string _file;
	WadAction _action;
	
public:
	Wad(const std::string &file, WadAction action);
	bool Prepare();
	void Install();
};

#endif