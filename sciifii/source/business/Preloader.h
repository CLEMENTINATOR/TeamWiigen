#ifndef PRELOADER_H_
#define PRELOADER_H_

#include "common/Installer.h"
#include <ogcsys.h>
#include <libutils/com/Buffer.h>

class Preloader : public Installer
{
private:
    u32 bootCid;
	std::string _url;
	std::string _sha;
	
	Buffer GetSysMenuTMD();
	u32 GetBootCid(tmd* t);
	void CopyTicket();
	void CopySysMenu();
	void RestoreSysMenu();
	bool CheckPreloader();
	
public:
	Preloader(const std::string& url, const std::string& sha);
	bool Prepare();
	void Install();
};

#endif
