#ifndef WEBLOGGER_H_
#define WEBLOGGER_H_

#include <string>
#include "ILogProvider.h"
namespace Libwiisys {
namespace Logging{

/**
 * @class WebLogger
 * @version 1.0
 * @author Teton,Arasium,Fanta
 * @brief Handle logging over the network
 * 
 * This class can log data using get method into your website, you just have to read the key and the parameters form your website 
 * and do whatever you like to do
 */
class WebLogger : public ILogProvider 
{
public:
	WebLogger(const std::string& url,const std::string& msgKey, const std::string& lineKey, const std::string& fileKey, const std::string& appKey, const std::string& versionKey);
	virtual ~WebLogger();
	void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteInfo(const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void Write(const std::string& type, const std::string& message, int line,const char* file, const std::string& appName, const std::string& appVersion);
	void Start();
	void Pause();
private :
	std::string _url;
	std::string _msgKey;
	std::string _lineKey;
	std::string _fileKey;
	std::string _appKey;
	std::string _versionKey;
};
}
}
#endif /* WEBLOGGER_H_ */
