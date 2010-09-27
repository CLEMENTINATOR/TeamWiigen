#ifndef _GECKO_LOGGER_H_
#define _GECKO_LOGGER_H_

#include "../Object.h"
#include "ILogProvider.h"
namespace Libwiisys {
	namespace Logging {

		/**
		 * @class GeckoLogger
		 * @version 1.0
		 * @author Teton,Arasium,fanta
		 * @brief This class handle the logging on a USB gecko
		 */
		class GeckoLogger : public Object, public ILogProvider
		{
		private:

			/**
			 *\brief Write a text to gecko output
			 *\param text The text to write
			 */
			void Write(const std::string& line);

			/**
			 * \brief Initialise a gecko log
			 */
			static void Initialize();
		public:
            	virtual std::string GetType();
			/**
			 *\brief Constructor
			 */
			GeckoLogger();

			/**
			 *\brief Destructor
			 */
			virtual ~GeckoLogger();

			/**
			 * @brief Write an error to the GeckoLogger
			 * @param message The message
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write an warning to the GeckoLogger
			 * @param message The message
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write an information to the GeckoLogger
			 * @param message The message
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteInfo(const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write a debug information to the GeckoLogger
			 * @param message The message
			 * @param line The line where the error occured
			 * @param file The file where the error occured
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteDebug( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 *@brief Start the logging
			 */
			void Start();

			/**
			 *@brief Pause the logging
			 */
			void Pause();
			virtual void Init(std::string appName, std::string appVersion);
		};
	}
}
#endif

