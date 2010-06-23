#ifndef _FILE_LOGGER_H_
#define _FILE_LOGGER_H_

#include "../Object.h"
#include "../IO/File.h"
#include "ILogProvider.h"

namespace Libwiisys {
	namespace Logging{

class FileLogger : public Object, public ILogProvider
{
private:
	Libwiisys::IO::File* _logFile;
	std::string _filePath;
	bool paused;
	void Write(const std::string& line);
public:
	FileLogger(const std::string& filePath);
	~FileLogger();
	void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void WriteInfo( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);
	void Start();
	void Pause();
};

}
}
#endif

