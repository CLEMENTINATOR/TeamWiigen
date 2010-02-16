#ifndef WADBATCHINSTALLER_H_
#define WADBATCHINSTALLER_H_

#include "common/Installer.h"


class WadBatchInstaller : public Installer
{
private:
	std::string _wadFolder;

public:
	WadBatchInstaller(const std::string &folder);
	bool Prepare();
	void Install();
};

#endif
