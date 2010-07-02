#include <libwiisys.h>
#include <sstream>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Logging;

/**
 *\brief Constructor,Open the file when you want to log data
 *\param filePath The log file path
 */
FileLogger::FileLogger(const std::string& filePath):_filePath(filePath)
{
	if(File::Exists(filePath))
		File::Delete(filePath);
	paused=true;

}

/**
 *\brief Destructor, Close the log file handle
 */
FileLogger::~FileLogger()
{
	if(!paused)
	{
		_logFile->Close();
		delete _logFile;
	}
}

/**
 * @brief Start the logging
 */
void FileLogger::Start()
{
	if(! paused)return;

	if(!File::Exists(_filePath)) _logFile = &(File::Create(_filePath));
	else _logFile = &(File::Open(_filePath,FileMode_Write));
	paused=false;
}

/**
 * @brief Pause the logging
 */
void FileLogger::Pause()
{
	if(paused) return;
	_logFile->Close();
	delete _logFile;
	paused=true;
}

/**
 * \brief Write a string to the log file
 * \param line The string you want to write in
 */
void FileLogger::Write(const std::string& line)
{
	if(paused) Start();
	string endLine = "\n";

	Buffer message(line.c_str(), line.length());
	message.Append(endLine.c_str(), endLine.length());

	_logFile->Write(message);
}

/**
 * @brief Write an error to the FileLogger
 * @param message The message
 * @param line The line where the error occured
 * @param file The file where the error occured
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void FileLogger::WriteError( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Error " << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

/**
 * @brief Write an warning to the FileLogger
 * @param message The message
 * @param line The line where the error occured
 * @param file The file where the error occured
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void FileLogger::WriteWarning( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Warning " << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

/**
 * @brief Write an information to the FileLogger
 * @param message The message
 * @param line The line where the error occured
 * @param file The file where the error occured
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void FileLogger::WriteInfo( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Info " << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}
