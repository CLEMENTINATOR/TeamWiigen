#include <libwiisys.h>
#include <string>
#include <vector>

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Network;

/**
 * @brief Constructor
 * @param url The url where the WebLogger'll log
 * @param msgKey The msgkey for GET request ( meskey="value")
 * @param lineKey Same as above
 * @param fileKey Same as above
 * @param appKey Same as above
 * @param versionKey Same as above
 */
WebLogger::WebLogger(const string& url,const string& msgKey, const string& lineKey, const string& fileKey, const string& appKey, const string& versionKey) 
: _url(url),
  _msgKey(msgKey),
  _lineKey(lineKey),
  _fileKey(fileKey), 
  _appKey(appKey),
  _versionKey(versionKey)
{}

/**
 * \brief Destructor
 */
WebLogger::~WebLogger() {}

/**
 * @brief Write an error to the WebLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void WebLogger::WriteError( const string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	Write("ERR", message, line, file, appName, appVersion);
}

/**
 * @brief Write an warning to the WebLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void WebLogger::WriteWarning( const string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	Write("WAR", message, line, file, appName, appVersion);
}

/**
 * @brief Write an info to the WebLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void WebLogger::WriteInfo( const string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	Write("NFO", message, line, file, appName, appVersion);
}

/**
 * @brief Write an text to the WebLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void WebLogger::Write(const string& type, const string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	try
	{
		HttpRequest r(_url);

		r.AddParameter("type", type);

		if(_msgKey != "")
			r.AddParameter(_msgKey, message);

		stringstream str_line;
		str_line << line;
		if(_lineKey != "")
			r.AddParameter(_lineKey, str_line.str());

		if(_fileKey != "")
			r.AddParameter(_fileKey, file);

		if(_appKey != "")
			r.AddParameter(_appKey, appName);

		if(_versionKey != "")
			r.AddParameter(_versionKey, appVersion);

		r.GetResponse();
	}
	catch(...)
	{	}
}

/**
 *@brief Start the logging
 */
void WebLogger::Start() {}

/**
 *@brief Pause the logging
 */
void WebLogger::Pause() {}
