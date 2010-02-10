#ifndef _LOADER_GX_H_
#define _LOADER_GX_H_

#include <string>
#include "common/Installer.h"

class LoaderGX : public Installer
{	
private:
	std::string _language;
	
	std::string GetLanguage();
	
public:
	LoaderGX(const std::string& workingDirectory);
	bool Prepare();
	void Install();
};

#endif
