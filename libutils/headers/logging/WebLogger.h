/*
 * WebLogger.h
 *
 *  Created on: 10 juin 2010
 *      Author: Clement
 */

#ifndef WEBLOGGER_H_
#define WEBLOGGER_H_
#include <string>
#include <UtilString.h>
#include <logging/ILogProvider.h>
class WebLogger : ILogProvider {
public:
	WebLogger(std::string _url);
	virtual ~WebLogger();
	void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteInfo(const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void Write( const std::string& text );
private :
	std::string _url;
};

#endif /* WEBLOGGER_H_ */
