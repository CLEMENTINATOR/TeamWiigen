#ifndef _ILOGPROVIDER_H_
#define _ILOGPROVIDER_H_

#include <string>
#include <gctypes.h>
namespace Libwiisys {
	namespace Logging{
typedef enum
{
	Lgt_Error = 1,
	Lgt_Warning = 2,
	Lgt_Info = 4,
	Lgt_All = 7,
} LogType;

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
