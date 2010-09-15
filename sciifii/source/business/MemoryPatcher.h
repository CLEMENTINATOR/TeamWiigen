#ifndef MEMORYPATCHER_H_
#define MEMORYPATCHER_H_

#include "common/Installer.h"


class MemoryPatcher : public Installer
{
public:
	MemoryPatcher();
	bool Prepare();
	void Install();
	void SendToLog();
};

#endif
