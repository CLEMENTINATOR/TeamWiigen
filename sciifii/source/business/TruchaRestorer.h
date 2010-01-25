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
	TruchaRestorer(u64 titleId, u16 revision, const std::string& wadFolder);
	bool Prepare();
	void Install();
};

#endif