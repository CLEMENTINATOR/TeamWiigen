#ifndef _SYS_UPDATER_H_
#define _SYS_UPDATER_H_

#include <string>
#include <fastdelegate.h>

#include "../Config.h"
#include "common/Installer.h"

class SystemUpdater : public Installer
{
private:
	std::vector<titleDescriptor> _titleList;
public:
	SystemUpdater(const std::vector<titleDescriptor>& titleList, const std::string& workingDirectory);
	bool Prepare();
	void Install();
};
#endif
