#ifndef _FILE_LOGGER_H_
#define _FILE_LOGGER_H_

#include "../Object.h"
#include "../fs/File.h"
#include "ILogProvider.h"

class FileLogger : public Object, public ILogProvider
{
private:
	File* _logFile;
	
	void Write(const std::string& line);
public:
	FileLogger(const std::string& filePath);
	~FileLogger();
	void WriteError(const std::string& source, const std::string& message, s32 errorCode);
	void WriteWarning(const std::string& source, const std::string& message, s32 warningCode);
	void WriteInfo(const std::string& source, const std::string& message, s32 infoCode);
};

#endif

