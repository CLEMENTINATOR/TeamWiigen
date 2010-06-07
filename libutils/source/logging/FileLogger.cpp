#include <logging/FileLogger.h>
#include <sstream>

using namespace std;
/**
 *\brief Constructor,Open the file when you want to log data
 * \param filePath The log file path
 */
FileLogger::FileLogger(const std::string& filePath)
{
	if(File::Exists(filePath))
		File::Delete(filePath);
		
	_logFile = &(File::Create(filePath));
}
/**
 *\brief Destructor, Close the log file handle
 */
FileLogger::~FileLogger()
{
	_logFile->Close();
	delete _logFile;
}
/**
 * \brief Write a string to the log file
 * \param line The string you want to write in
 */
void FileLogger::Write(const std::string& line)
{
	string endLine = "\n";
	
	Buffer message(line.c_str(), line.length());
	message.Append(endLine.c_str(), endLine.length());
	
	_logFile->Write(message);
}

void FileLogger::WriteError(const std::string& source, const std::string& message, s32 errorCode)
{
	stringstream formatedMessage;
	formatedMessage << "Error " << errorCode << " (" << source << "): " << message;
	Write(formatedMessage.str());
}

void FileLogger::WriteWarning(const std::string& source, const std::string& message, s32 warningCode)
{
	stringstream formatedMessage;
	formatedMessage << "Warning " << warningCode << " (" << source << "): " << message;
	Write(formatedMessage.str());
}

void FileLogger::WriteInfo(const std::string& source, const std::string& message, s32 infoCode)
{
	stringstream formatedMessage;
	formatedMessage << "Info " << infoCode << " (" << source << "): " << message;
	Write(formatedMessage.str());
}
