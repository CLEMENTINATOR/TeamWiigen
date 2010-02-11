#ifndef PRELOADER_H_
#define PRELOADER_H_

#include "common/Installer.h"
#include <ogcsys.h>
#include <libutils/com/Buffer.h>

class Preloader : public Installer
{
private:
    u32 bootCid;
	
	Buffer GetSysMenuTMD();
	u32 GetBootCid(tmd* t);
	void CopyTicket();
	void CopySysMenu();
	void RestoreSysMenu();
	bool CheckPreloader();
	
public:
	Preloader();
	bool Prepare();
	void Install();
};

#endif
