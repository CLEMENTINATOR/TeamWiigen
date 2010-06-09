#include <logging/FileLogger.h>
#include <sstream>

using namespace std;
/**
 *\brief Constructor,Open the file when you want to log data
 * \param filePath The log file path
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
void FileLogger::Start()
{
	if(! paused)return;

	if(!File::Exists(_filePath)) _logFile = &(File::Create(_filePath));
		_logFile = &(File::Open(_filePath,FileMode_Write));
		paused=false;
}
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

void FileLogger::WriteError( const std::string& message, s32 errorCode,int line,const char* file)
{
	stringstream formatedMessage;
	formatedMessage << "Error " << errorCode << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

void FileLogger::WriteWarning( const std::string& message, s32 warningCode,int line,const char* file)
{
	stringstream formatedMessage;
	formatedMessage << "Warning " << warningCode<< " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

void FileLogger::WriteInfo( const std::string& message, s32 infoCode,int line,const char* file)
{
	stringstream formatedMessage;
	formatedMessage << "Info " << infoCode << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}
