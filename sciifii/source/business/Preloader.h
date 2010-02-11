#ifndef PRELOADER_H_
#define PRELOADER_H_

#include "common/Installer.h"
#include <gctypes.h>

class Preloader : public Installer
{
private:
    u32 bootCid;
public:
	Preloader();
	bool Prepare();
	void Install();
};

#endif
