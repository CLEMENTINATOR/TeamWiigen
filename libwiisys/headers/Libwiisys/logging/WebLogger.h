#ifndef WEBLOGGER_H_
#define WEBLOGGER_H_

#include <string>
#include "ILogProvider.h"
namespace Libwiisys {
	namespace Logging {

		/**
		 * @class WebLogger
		 * @version 1.0
		 * @author Teton,Arasium,Fanta
		 * @brief Handle logging over the network
		 *
		 * This class can log data using get method into your website, you just have to read the key and the parameters form your website
		 * and do whatever you like to do
		 */
		class WebLogger : public Object,public ILogProvider
		{
		public:
				virtual std::string GetType();
			/**
			 * @brief Constructor
			 * @param url The url where the WebLogger'll log
			 * @param msgKey The msgkey for GET request ( meskey="value")
			 * @param lineKey Same as above
			 * @param fileKey Same as above
			 * @param appKey Same as above
			 * @param versionKey Same as above
			 */
			WebLogger(const std::string& url,const std::string& msgKey, const std::string& lineKey, const std::string& fileKey, const std::string& appKey, const std::string& versionKey);

			/**
			 * \brief Destructor
			 */
			virtual ~WebLogger();

			/**
			 * @brief Write an error to the WebLogger
			 * @param message The message
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write an warning to the WebLogger
			 * @param message The message
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write an info to the WebLogger
			 * @param message The message
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteInfo(const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write a debug information to the WebLogger
			 * @param message The message
			 * @param line The line where the error occured
			 * @param file The file where the error occured
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void WriteDebug( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 * @brief Write an text to the WebLogger
			 * @param message The message
			 * @param type Type of the log(ERR,WAR,NFO)
			 * @param line The line where the error occurred
			 * @param file The file where the error occurred
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			void Write(const std::string& type, const std::string& message, int line,const char* file, const std::string& appName, const std::string& appVersion);

			/**
			 *@brief Start the logging
			 */
			void Start();

			/**
			 *@brief Pause the logging
			 */
			void Pause();
		        void Init(std::string appName, std::string appVersion);
		private :
			std::string _url;
			std::string _msgKey;
			std::string _lineKey;
			std::string _fileKey;
			std::string _appKey;
			std::string _versionKey;
		};
	}
}
#endif /* WEBLOGGER_H_ */
