#include <Libwiisys/logging/WebLogger.h>
#include <string>
#include <vector>
#include <Libwiisys/Network/HttpRequest.h>

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Network;

WebLogger::WebLogger(const string& url, const string& msgKey,
                     const string& lineKey, const string& fileKey, const string& appKey,
                     const string& versionKey) :
    _url(url), _msgKey(msgKey), _lineKey(lineKey), _fileKey(fileKey), _appKey(
      appKey), _versionKey(versionKey)
{
}

void WebLogger::Init(std::string appName, std::string appVersion)
{
  try
  {
    HttpRequest r(_url);

    r.AddParameter("action", "init");
    r.AddParameter(_appKey, appName);
    r.AddParameter(_versionKey,appVersion);
    r.GetResponse();
  }
  catch (...)
  {}
}

WebLogger::~WebLogger()
{}

void WebLogger::WriteError(const string& message, int line, const char* file,
                           const string& appName, const string& appVersion)
{
  Write("ERR", message, line, file, appName, appVersion);
}

void WebLogger::WriteWarning(const string& message, int line, const char* file,
                             const string& appName, const string& appVersion)
{
  Write("WAR", message, line, file, appName, appVersion);
}

void WebLogger::WriteInfo(const string& message, int line, const char* file,
                          const string& appName, const string& appVersion)
{
  Write("NFO", message, line, file, appName, appVersion);
}

void WebLogger::WriteDebug(const string& message, int line, const char* file,
                           const string& appName, const string& appVersion)
{
  Write("DBG", message, line, file, appName, appVersion);
}

void WebLogger::Write(const string& type, const string& message, int line,
                      const char* file, const string& appName, const string& appVersion)
{
  try
  {
    HttpRequest r(_url);

    r.AddParameter("type", type);

    if (_msgKey != "")
      r.AddParameter(_msgKey, message);

    stringstream str_line;
    str_line << line;
    if (_lineKey != "")
      r.AddParameter(_lineKey, str_line.str());

    if (_fileKey != "")
      r.AddParameter(_fileKey, file);

    if (_appKey != "")
      r.AddParameter(_appKey, appName);

    if (_versionKey != "")
      r.AddParameter(_versionKey, appVersion);

    r.GetResponse();
  }
  catch (...)
  {}
}

void WebLogger::Start()
{}

void WebLogger::Pause()
{}

std::string WebLogger::GetType()
{
  return "Libwiisys::Logging::WebLogger,"+Object::GetType();
}
