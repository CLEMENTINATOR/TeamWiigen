#include <gccore.h>
#include <sstream>
#include <libwiisys.h>

using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace std;

GeckoLogger::GeckoLogger() {
	GeckoLogger::Initialize();
}

void GeckoLogger::Initialize() {
	static bool initialised = false;
	if (!initialised) {
		if (usb_isgeckoalive(EXI_CHANNEL_1)) {
			usb_flush(EXI_CHANNEL_1);
			initialised = true;
		} else
			throw Exception("Pb with gecko!");
	}
}

GeckoLogger::~GeckoLogger() {
}


void GeckoLogger::Init(std::string appName, std::string appVersion)
{
}
void GeckoLogger::WriteError(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Error " << " (" << file << " line : " << line << "): "
			<< message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteWarning(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Warning " << " (" << file << " line : " << line
			<< "): " << message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteInfo(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Info " << " (" << file << " line : " << line << "): "
			<< message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteDebug(const std::string& message, int line,
		const char* file, const string& appName, const string& appVersion) {
	stringstream formatedMessage;
	formatedMessage << "Debug " << " (" << file << " line : " << line << "): "
			<< message;
	Write(formatedMessage.str());
}

void GeckoLogger::Write(const std::string& text) {
	string sendText(text + "\n");
	usb_sendbuffer_safe(1, sendText.c_str(), sendText.size() + 1);
}

void GeckoLogger::Start() {
}

void GeckoLogger::Pause() {
}

std::string GeckoLogger::GetType()
{
	return "Libwiisys::Logging::GeckoLogger,"+Object::GetType();
}
