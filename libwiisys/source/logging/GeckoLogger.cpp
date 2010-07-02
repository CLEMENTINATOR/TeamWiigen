#include <gccore.h>
#include <sstream>
#include <libwiisys.h>

using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
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

/**
 * @brief Write an error to the GeckoLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void GeckoLogger::WriteError( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Error " << " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

/**
 * @brief Write an warning to the GeckoLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
void GeckoLogger::WriteWarning( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "Warning "<< " (" << file << " line : "<<line <<"): " << message;
	Write(formatedMessage.str());
}

/**
 * @brief Write an information to the GeckoLogger
 * @param message The message
 * @param line The line where the error occurred
 * @param file The file where the error occurred
 * @param appName The application name
 * @param appVersion The application version
 * @see WriteLog(status,message)
 */
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
/**
 *@brief Start the logging
 */
void GeckoLogger::Start() {}

/**
 *@brief Pause the logging
 */
void GeckoLogger::Pause() {}
