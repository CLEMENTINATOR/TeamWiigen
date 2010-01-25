#ifndef _TITLE_INSTALLER_H_
#define _TITLE_INSTALLER_H_

#include "common/Installer.h"

class TitleInstaller : public Installer
{
private:
	u64 _id;
	u16 _revision;

public:
	TitleInstaller(u64 titleId, u16 revision, const std::string& wadFolder);
	bool Prepare();
	void Install();
};

#endif
