#ifndef _GECKO_LOGGER_H_
#define _GECKO_LOGGER_H_

#include "../Object.h"
#include "ILogProvider.h"
namespace Libwiisys {
namespace Logging{

/**
 * @class GeckoLogger
 * @version 1.0
 * @author Teton,Arasium,fanta
 * @brief This class handle the logging on a USB gecko
 */
class GeckoLogger : public Object, public ILogProvider
{
private:
	void Write(const std::string& line);
	static void Initialize();
public:
	GeckoLogger();
	virtual ~GeckoLogger();
	void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteInfo(const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void Start();
	void Pause();
};
}
}
#endif


