#include <logging/Log.h>

using namespace std;

Log::Log()
{
	_logs.insert(make_pair(Log_Error, new vector<ILogProvider*>()));
	_logs.insert(make_pair(Log_Warning, new vector<ILogProvider*>()));
	_logs.insert(make_pair(Log_Info, new vector<ILogProvider*>()));
}

Log::~Log()
{
	for(map<LogStatus, vector<ILogProvider*>*>::iterator ite = _logs.begin(); ite != _logs.end(); ite++)
		delete ite->second;
}

Log& Log::Current()
{
	static Log l;
	return l;
}

void Log::AddLogProvider(LogStatus status, ILogProvider* logger)
{
	if((status & Log_Error) == Log_Error)
		Current()._logs.find(Log_Error)->second->push_back(logger);
		
	if((status & Log_Warning) == Log_Warning)
		Current()._logs.find(Log_Warning)->second->push_back(logger);
	
	if((status & Log_Info) == Log_Info)
		Current()._logs.find(Log_Info)->second->push_back(logger);
}

void Log::Write(LogStatus status, const std::string& source, const std::string& message, s32 code)
{
	for(map<LogStatus, vector<ILogProvider*>*>::iterator ite = Current()._logs.begin(); ite != Current()._logs.end(); ite++)
	{
		if((ite->first & status) > 0)
			for(vector<ILogProvider*>::iterator lite = ite->second->begin(); lite != ite->second->end(); lite++)
			{
				if((ite->first & Log_Error) == Log_Error)
					(*lite)->WriteError(source, message, code);
					
				if((ite->first & Log_Warning) == Log_Warning)
					(*lite)->WriteWarning(source, message, code);
				
				if((ite->first & Log_Info) == Log_Info)
					(*lite)->WriteInfo(source, message, code);
			}
	}
}