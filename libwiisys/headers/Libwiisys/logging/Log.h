#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <gctypes.h>
#include <vector>
#include <map>

#include "../Object.h"
#include "ILogProvider.h"
#include "LogStatus.h"

#define WriteLog(status,message) Write(status,message, __LINE__ , __FILE__ )

/*! \namespace Libwiisys::Logging
 * \brief Logging system
 *
 * The log system is made with a Log class and a provider.
 * You only need to implement the ILogProvider to create a new log
 * format.
 */

namespace Libwiisys {
	namespace Logging {

		/**
		 * @brief Log class
		 * @version 1.0
		 * @author Arasium,Teton,Fanta
		 */
		class Log : public Object
		{
		private:
			bool _hasLog;
			bool _isInit;
			std::string _appName;
			std::string _appVersion;

			/**
			 * \brief Constructor
			 * Initialize log system
			 */
			Log();

			/**
			 *\brief Destructor
			 */
			~Log();

			/**
			 * \brief Return the current log system
			 * \return The log system
			 */
			static Log& Current();

			std::map<LogStatus, std::vector<ILogProvider*>*> _logs;

		public:

			/**
			 *\brief Add a log provider to the log system
			 *\param type The LogType associed to the provider
			 *\param logger The Log provider ( Could be FileLogger or GekkoLogger)
			 *\see LogStatus
			 */
			static void AddLogProvider(LogType type, ILogProvider* logger);

			/**
			 *\brief Init logging subsystems
			 * \param appName The name of the application
			 * \param appVersion The version of the application
			 */
			static void Init(std::string appName, std::string appVersion);

			/**
			 *\brief Pause all the logging subsystems
			 */
			static void Pause();

			/**
			 *\brief Write to logs
			 *\param status The LogStatus associated to the message to write
			 *\param message The message to write
			 *\param line The line where the fonction call has occurred
			 *\param file The file where the fonction call has occurred
			 */
			static void Write(LogStatus status, const std::string& message,int line,const char* file);
		};
	}
}
#endif
