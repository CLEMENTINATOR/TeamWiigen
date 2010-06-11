#ifndef _COMMON_INSTALLER_H_
#define _COMMON_INSTALLER_H_

#include <string>
#include <gctypes.h>
#include <libutils/Object.h>
#include <sstream>
#include <libutils/logging/Log.h>
#include <libutils/logging/ILogProvider.h>
#include "ProgressEvent.h"

class Installer : public Object
{
private:
	std::string _options;

protected:
	virtual void OnProgress(const std::string& message, f32 value);
	virtual void OnWarning(const std::string& message, f32 value);
public:
	std::string Options();
	void Options(const std::string& options);
	virtual void SendToLog();

	virtual bool Prepare() = 0;
	virtual void Install() = 0;
	ProgressEvent Progressing;
	ProgressEvent Warning;
	virtual ~Installer();
};

#endif
