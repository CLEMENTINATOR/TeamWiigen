#include <Libwiisys/logging/Log.h>

using namespace Libwiisys::Logging;
using namespace std;

Log::Log() :
    _hasLog(false), _isInit(false), _appName(""), _appVersion("")
{
  _logs.insert(make_pair(Log_Error, new vector<ILogProvider*> ()));
  _logs.insert(make_pair(Log_Warning, new vector<ILogProvider*> ()));
  _logs.insert(make_pair(Log_Info, new vector<ILogProvider*> ()));
  _logs.insert(make_pair(Log_Debug, new vector<ILogProvider*> ()));
}

Log::~Log()
{
  for (map<LogStatus, vector<ILogProvider*>*>::iterator ite = _logs.begin(); ite
       != _logs.end(); ite++)
    delete ite->second;
}

void Log::Pause()
{

  if (!Current()._hasLog)
    return;
  for (map<LogStatus, vector<ILogProvider*>*>::iterator ite =
         Current()._logs.begin(); ite != Current()._logs.end(); ite++)
  {
    for (vector<ILogProvider*>::iterator lite = ite->
         second->begin();
         lite
         != ite->second->end();
         lite++)
    {
      (*lite)->Pause();
    }
  }

}

Log& Log::Current()
{
  static Log l;
  return l;
}

void Log::AddLogProvider(LogType type, ILogProvider* logger)
{
  u8 status = (u8) type;
  if (status & (u8) Log_Error)
    Current()._logs.find(Log_Error)->second->push_back(logger);

  if (status & (u8) Log_Warning)
    Current()._logs.find(Log_Warning)->second->push_back(logger);

  if (status & (u8) Log_Info)
    Current()._logs.find(Log_Info)->second->push_back(logger);

  if (status & (u8) Log_Debug)
    Current()._logs.find(Log_Debug)->second->push_back(logger);

  Current()._hasLog = true;
  logger->Init(Current()._appName  ,Current()._appVersion);
}

void Log::Write(LogStatus status, const std::string& message, int line, const char* file)
{
  if (!Current()._hasLog || !Current()._isInit)
    return;

  for (map<LogStatus, vector<ILogProvider*>*>::iterator ite = Current()._logs.begin(); ite != Current()._logs.end(); ite++)
  {
    if ((ite->first & status) > 0)
      for (vector<ILogProvider*>::iterator lite = ite->
           second->begin();
           lite != ite->second->end();
           lite++)
      {
        if ((ite->first & Log_Error) == Log_Error)
          (*lite)->WriteError(message, line, file, Current()._appName, Current()._appVersion);

        if ((ite->first & Log_Warning) == Log_Warning)
          (*lite)->WriteWarning(message, line, file, Current()._appName, Current()._appVersion);

        if ((ite->first & Log_Info) == Log_Info)
          (*lite)->WriteInfo(message, line, file, Current()._appName, Current()._appVersion);

        if ((ite->first & Log_Debug) == Log_Debug)
          (*lite)->WriteDebug(message, line, file, Current()._appName, Current()._appVersion);
      }
  }
}

void Log::Init(std::string appName, std::string appVersion)
{
  Current()._appName = appName;
  Current()._appVersion = appVersion;
  Current()._isInit = true;
}

std::string Log::GetType()
{
  return "Libwiisys::Logging::Log,"+Object::GetType();
}
