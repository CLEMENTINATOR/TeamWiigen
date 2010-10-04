#ifndef _IOSRELOADER_H_
#define _IOSRELOADER_H_

#include <string>
#include <gctypes.h>
#include <libwiisys.h>

#include "common/Installer.h"

class IosReloader : public Installer
{
private:
	u32 _id;

public:
	IosReloader(u32 ios);
	bool Prepare();
	void SendToLog();

	void Install();
};

#endif
