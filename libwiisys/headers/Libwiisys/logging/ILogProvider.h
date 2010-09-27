#ifndef _ILOGPROVIDER_H_
#define _ILOGPROVIDER_H_

#include <string>
#include <gctypes.h>
#include "LogType.h"

namespace Libwiisys {
	namespace Logging {

		/**
		 * @interface ILogProvider
		 * @version 1.0
		 * @author Arasium,Teton,fanta
		 * @brief Interface reimplemented by logs
		 */
		class ILogProvider
		{
		public:
			/**
			 * @brief Destructor
			 */
			virtual ~ILogProvider() = 0;

			/**
			 * @brief Write an error (needs to be reimplemented in inherited class)
			 * @param message The message
			 * @param line The line where the error occured
			 * @param file The file where the error occured
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			virtual void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;

			/**
			 * @brief Write an warning (needs to be reimplemented in inherited class)
			 * @param message The message
			 * @param line The line where the error occured
			 * @param file The file where the error occured
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			virtual void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;

			/**
			 * @brief Write an info (needs to be reimplemented in inherited class)
			 * @param message The message
			 * @param line The line where the error occured
			 * @param file The file where the error occured
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			virtual void WriteInfo( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;

			/**
			 * @brief Write a debug (needs to be implemented in inherited class)
			 * @param message The message
			 * @param line The line where the error occured
			 * @param file The file where the error occured
			 * @param appName The application name
			 * @param appVersion The application version
			 * @see WriteLog(status,message)
			 */
			virtual void WriteDebug( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion) = 0;


			/**
			 * @brief Start the logging(needs to be reimplemented in inherited class)
			 */
			virtual void Start()=0;

			/**
			 * @brief Pause the logging(needs to be reimplemented in inherited class)
			 */
			virtual void Pause()=0;
			virtual void Init(std::string appName, std::string appVersion)=0;
		};
	}
}
#endif
