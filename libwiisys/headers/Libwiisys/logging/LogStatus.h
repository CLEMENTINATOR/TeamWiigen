#ifndef LOGSTATUS_H_
#define LOGSTATUS_H_

namespace Libwiisys
{
  namespace Logging
  {

    /**
     * @enum LogStatus
     * @brief Reprensents a log status message
     */
    typedef enum
    {
      Log_Error = 1, //!< Log_Error
      Log_Warning = 2,//!< Log_Warning
      Log_Info = 4, //!< Log_Info
      Log_Debug = 8,
    }LogStatus;

  }
}

#endif /* LOGSTATUS_H_ */
