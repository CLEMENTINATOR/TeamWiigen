#ifndef _GECKO_LOGGER_H_
#define _GECKO_LOGGER_H_

#include "../Object.h"
#include "ILogProvider.h"

class GeckoLogger : public Object, public ILogProvider
{
private:
	void Write(const std::string& line);
	static void Initialize();
public:
	GeckoLogger();
	~GeckoLogger();
	void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteInfo(const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void Start();
	void Pause();
};

#endif


