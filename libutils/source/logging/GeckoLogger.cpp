#include <logging/FileLogger.h>
#include <logging/GeckoLogger.h>
#include <sstream>

using namespace std;

GeckoLogger::GeckoLogger(const std::string& filePath)
{
	u32 geckoattached = usb_isgeckoalive(EXI_CHANNEL_1);
	if (geckoattached)
	{
		usb_flush(EXI_CHANNEL_1);
		initialised= true;
		return;
	}
	initialised= false;
}

GeckoLogger::~GeckoLogger()
{
}

void GeckoLogger::WriteError(const std::string& source, const std::string& message, s32 errorCode)
{
	stringstream formatedMessage;
	formatedMessage << "Error " << errorCode << " (" << source << "): " << message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteWarning(const std::string& source, const std::string& message, s32 warningCode)
{
	stringstream formatedMessage;
	formatedMessage << "Warning " << warningCode << " (" << source << "): " << message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteInfo(const std::string& source, const std::string& message, s32 infoCode)
{
    stringstream formatedMessage;
	formatedMessage << "Info " << infoCode << " (" << source << "): " << message;
	Write(formatedMessage.str());
}

void GeckoLogger::Write( const std::string& text )
{
	if (!(initialised))return;
	usb_sendbuffer_safe( 1, text.c_str(), text.size() );
}
