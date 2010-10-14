#ifndef _FILE_LOGGER_H_
#define _FILE_LOGGER_H_

#include "../Object.h"
#include "../IO/File.h"
#include "ILogProvider.h"

namespace Libwiisys
{
  namespace Logging
  {

    /**
     * @class FileLogger
     * @version 1.0
     * @author Teton,Arasium,fanta
     * @brief This class handle logging into a file
     */
    class FileLogger : public Object, public ILogProvider
    {
      private:
        Libwiisys::IO::File* _logFile;
        std::string _filePath;
        bool paused;

        /**
         * \brief Write a string to the log file
         * \param line The string you want to write in
         */
        void Write(const std::string& line);

      public:
        virtual std::string GetType();
        /**
         *\brief Constructor,Open the file when you want to log data
         *\param filePath The log file path
         */
        FileLogger(const std::string& filePath);

        /**
         *\brief Destructor, Close the log file handle
         */
        virtual ~FileLogger();

        /**
         * @brief Write an error to the FileLogger
         * @param message The message
         * @param line The line where the error occured
         * @param file The file where the error occured
         * @param appName The application name
         * @param appVersion The application version
         * @see WriteLog(status,message)
         */
        void WriteError( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

        /**
         * @brief Write an warning to the FileLogger
         * @param message The message
         * @param line The line where the error occured
         * @param file The file where the error occured
         * @param appName The application name
         * @param appVersion The application version
         * @see WriteLog(status,message)
         */
        void WriteWarning( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

        /**
         * @brief Write an information to the FileLogger
         * @param message The message
         * @param line The line where the error occured
         * @param file The file where the error occured
         * @param appName The application name
         * @param appVersion The application version
         * @see WriteLog(status,message)
         */
        void WriteInfo( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

        /**
         * @brief Write a debug information to the FileLogger
         * @param message The message
         * @param line The line where the error occured
         * @param file The file where the error occured
         * @param appName The application name
         * @param appVersion The application version
         * @see WriteLog(status,message)
         */
        void WriteDebug( const std::string& message,int line,const char* file, const std::string& appName, const std::string& appVersion);

        /**
         * @brief Start the logging
         */
        void Start();

        /**
         * @brief Pause the logging
         */
        void Pause();
        void Init(std::string appName, std::string appVersion);
    };

  }
}
#endif

