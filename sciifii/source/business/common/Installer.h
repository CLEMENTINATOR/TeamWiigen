#ifndef _COMMON_INSTALLER_H_
#define _COMMON_INSTALLER_H_

#include <string>
#include <gctypes.h>
#include <libutils/Object.h>

#include "ProgressEvent.h"

class Installer : public Object
{
protected:
	std::string wadFolder;
	Installer(const std::string& folder = "");
	virtual void OnProgress(const std::string& message, f32 value);
	virtual void OnWarning(const std::string& message, f32 value);

public:
	virtual bool Prepare() = 0;
	virtual void Install() = 0;
	ProgressEvent Progressing;
	ProgressEvent Warning;
	virtual ~Installer();

protected:
};

#endif
