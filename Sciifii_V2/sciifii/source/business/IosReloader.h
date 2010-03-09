#ifndef _IOSRELOADER_H_
#define _IOSRELOADER_H_

#include <string>
#include <gctypes.h>
#include <libutils/system/Identification.h>

#include "common/Installer.h"

class IosReloader : public Installer
{
private:
	u32 _id;
	std::string _device;
	bool _identify;
	UserType _type;
	
public:
	IosReloader(u32 ios, const std::string& deviceToManage = "");
	IosReloader(u32 ios, UserType type, const std::string& deviceToManage = "");
	bool Prepare();
	void Install();
};

#endif
