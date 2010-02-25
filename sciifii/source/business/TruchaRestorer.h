#ifndef _TRUCHA_RESTORER_H_
#define _TRUCHA_RESTORER_H_

#include <libutils/system/Title.h>
#include "common/Installer.h"

class TruchaRestorer : public Installer
{
private:
	u64 _id;
	u16 _revision;

public:
	TruchaRestorer(u32 titleId, u16 revision);
	bool Prepare();
	void Install();
};

#endif
