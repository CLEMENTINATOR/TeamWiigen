#ifndef _COMMON_INSTALLER_H_
#define _COMMON_INSTALLER_H_

#include <string>
#include <gctypes.h>
#include <libwiisys/Object.h>
#include <sstream>
#include <libwiisys/logging/Log.h>
#include <libwiisys/logging/ILogProvider.h>
#include "ProgressEvent.h"

class Installer : public Libwiisys::Object
{
private:
	std::string _options;
	s8 _region;

protected:
	virtual void OnProgress(const std::string& message, f32 value);
	virtual void OnWarning(const std::string& message, f32 value);
public:
	std::string Options();
	void Options(const std::string& options);
	s8 Region();
	void Region(s8 r);

	virtual void SendToLog();

	virtual bool Prepare() = 0;
	virtual void Install() = 0;
	ProgressEvent Progressing;
	ProgressEvent Warning;
	virtual ~Installer();
};

#endif
