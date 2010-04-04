#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <gctypes.h>
#include <vector>
#include <map>

#include "../Object.h"
#include "ILogProvider.h"

typedef enum
{
	Log_Error = 1,
	Log_Warning = 2,
	Log_ErrorAndWarning = 3,
	Log_Info = 4,
	Log_InfoAndError = 5,
	Log_InfoAndWarning = 6,
	Log_All = 7,
} LogStatus;

class Log : public Object
{
private:
	Log();
	~Log();
	static Log& Current();
	
	std::map<LogStatus, std::vector<ILogProvider*>*> _logs;
	
public:
	static void AddLogProvider(LogStatus status, ILogProvider* logger);
	static void Write(LogStatus status, const std::string& source, const std::string& message, s32 code); 
};

#endif