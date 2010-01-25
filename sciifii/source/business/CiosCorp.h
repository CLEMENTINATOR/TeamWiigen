#ifndef CIOSCORP_H_
#define CIOSCORP_H_

#include <string>
#include <fastdelegate.h>
#include <libutils/Object.h>

#include "common/Installer.h"

class CiosCorp : public Installer
{
public:
	CiosCorp(const std::string& workingDirectory);
	bool Prepare();
	void Install();
};
#endif
