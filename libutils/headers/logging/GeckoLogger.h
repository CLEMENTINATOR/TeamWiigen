#ifndef _GECKO_LOGGER_H_
#define _GECKO_LOGGER_H_

#include "../Object.h"
#include "../fs/File.h"
#include "ILogProvider.h"

class GeckoLogger : public Object, public ILogProvider
{
private:
	void Write(const std::string& line);
	bool initialised;
public:
	GeckoLogger(const std::string& filePath);
	~GeckoLogger();
	void WriteError(const std::string& source, const std::string& message, s32 errorCode);
	void WriteWarning(const std::string& source, const std::string& message, s32 warningCode);
	void WriteInfo(const std::string& source, const std::string& message, s32 infoCode);
};

#endif


