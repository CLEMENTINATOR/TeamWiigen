#ifndef _SYS_UPDATER_H_
#define _SYS_UPDATER_H_

#include <string>
#include <fastdelegate.h>

#include "../Config.h"
#include "common/Installer.h"

typedef struct
{
	u64 slot;
	u64 title;
	u16 revision;
	bool onlyOnUninstall;
} titleDescriptor;

class SystemUpdater : public Installer
{
public:
	bool Prepare();
	void Install();
	void SendToLog();
	void AddTitle(const titleDescriptor& descriptor);
	
private:
	std::vector<titleDescriptor> _updateTitles;
};
#endif
