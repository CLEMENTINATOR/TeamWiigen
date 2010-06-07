#include <gccore.h>
#include <logging/GeckoLogger.h>
#include <sstream>
#include <exception/Exception.h>

using namespace std;
/**
*\brief Constructor
*/
GeckoLogger::GeckoLogger()
{
	GeckoLogger::Initialize();
}
/**
 * \brief Initialise a gecko log
 */
void GeckoLogger::Initialize()
{
	static bool initialised = false;
	if(!initialised)
	{
		if(usb_isgeckoalive(EXI_CHANNEL_1))
		{
			usb_flush(EXI_CHANNEL_1);
			initialised= true;
		}
		else
			throw Exception("Pb with gecko!", -1);
	}
}
/**
*\brief Destructor
*/
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
/**
 *\brief Write a text to gecko output
 *\param text The text to write
 */
void GeckoLogger::Write( const std::string& text )
{
	string sendText(text + "\n");
	usb_sendbuffer_safe( 1, sendText.c_str(), sendText.size() + 1 );
}
