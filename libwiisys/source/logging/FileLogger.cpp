#include <libwiisys.h>
#include <sstream>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Logging;

FileLogger::FileLogger(const std::string& filePath) :
	_filePath(filePath) {
	if (File::Exists(filePath))
		File::Delete(filePath);
	paused = true;

}

FileLogger::~FileLogger() {
	if (!paused) {
		_logFile->Close();
		delete _logFile;
	}
}

void FileLogger::Start() {
	if (!paused)
		return;

	if (!File::Exists(_filePath))
		_logFile = &(File::Create(_filePath));
	else
		_logFile = &(File::Open(_filePath, FileMode_Write));
	paused = false;
}

void FileLogger::Pause() {
	if (paused)
		return;
	_logFile->Close();
	delete _logFile;
	paused = true;
}

void FileLogger::Write(const std::string& line) {
	if (paused)
		Start();
	string endLine = "\n";

	Buffer message(line.c_str(), line.length());
	message.Append(endLine.c_str(), endLine.length());

	_logFile->Write(message);
}

void FileLogger::WriteError(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Error " << " (" << file << " line : " << line << "): "
			<< message;
	Write(formatedMessage.str());
}

void FileLogger::WriteWarning(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Warning " << " (" << file << " line : " << line
			<< "): " << message;
	Write(formatedMessage.str());
}

void FileLogger::WriteInfo(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Info " << " (" << file << " line : " << line << "): "
			<< message;
	Write(formatedMessage.str());
}

void FileLogger::WriteDebug(const std::string& message, int line, const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Debug " << " (" << file << " line : " << line << "): "
			<< message;
	Write(formatedMessage.str());
}
