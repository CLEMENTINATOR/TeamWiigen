#ifndef _SYS_UPDATER_H_
#define _SYS_UPDATER_H_

#include <string>
#include <fastdelegate.h>

#include "../Config.h"
#include "common/Installer.h"

class SystemUpdater : public Installer
{
public:
	bool Prepare();
	void Install();
};
#endif
