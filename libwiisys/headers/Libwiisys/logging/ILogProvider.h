#ifndef _ILOGPROVIDER_H_
#define _ILOGPROVIDER_H_

#include <string>
#include <gctypes.h>
#include "LogType.h"

namespace Libwiisys {
namespace Logging{

/**
 * @interface ILogProvider
 * @version 1.0
 * @author Arasium,Teton,fanta
 */
class ILogProvider
{
public:
	virtual ~ILogProvider() = 0;
	virtual void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;
	virtual void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;
	virtual void WriteInfo( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;
	virtual void Start()=0;
	virtual void Pause()=0;
};
}
}
#endif
