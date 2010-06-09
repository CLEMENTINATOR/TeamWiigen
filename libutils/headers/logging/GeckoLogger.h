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
	void WriteError( const std::string& message, s32 errorCode,int line,const char* file);
	void WriteWarning( const std::string& message, s32 warningCode,int line,const char* file);
	void WriteInfo(const std::string& message, s32 infoCode,int line,const char* file);
};

#endif


