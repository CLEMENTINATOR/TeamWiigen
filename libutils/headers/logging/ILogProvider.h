#ifndef _ILOGPROVIDER_H_
#define _ILOGPROVIDER_H_

#include <string>
#include <gctypes.h>

class ILogProvider
{
public:
	virtual ~ILogProvider() = 0;
	virtual void WriteError(const std::string& source, const std::string& message, s32 errorCode) = 0;
	virtual void WriteWarning(const std::string& source, const std::string& message, s32 warningCode) = 0;
	virtual void WriteInfo(const std::string& source, const std::string& message, s32 infoCode) = 0;
};

#endif