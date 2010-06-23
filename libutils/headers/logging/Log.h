#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <gctypes.h>
#include <vector>
#include <map>

#include "../Object.h"
#include "ILogProvider.h"
namespace Libwiisys {
	namespace Logging{
typedef enum
{
	Log_Error = 1,
	Log_Warning = 2,
	Log_Info = 4,
} LogStatus;

#define WriteLog(status,message) Write(status,message, __LINE__ , __FILE__ )

class Log : public Object
{
private:
	bool _hasLog;
	bool _isInit;
  std::string _appName;
  std::string _appVersion;
	Log();
	~Log();
	static Log& Current();
	
	std::map<LogStatus, std::vector<ILogProvider*>*> _logs;
	
public:
	static void AddLogProvider(LogType type, ILogProvider* logger);
  static void Init(std::string appName, std::string appVersion);
  static void Pause();
	static void Write(LogStatus status, const std::string& message,int line,const char* file);
};
}
}
#endif
