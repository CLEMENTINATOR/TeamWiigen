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

void GeckoLogger::WriteError( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Error " << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteWarning( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Warning "<< " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

void GeckoLogger::WriteInfo( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
    stringstream formatedMessage;
	formatedMessage << "Info " << " (" << file << " line : "<<line <<"): " << message;
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
