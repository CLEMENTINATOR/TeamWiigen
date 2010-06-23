#ifndef LOGSTATUS_H_
#define LOGSTATUS_H_

namespace Libwiisys {
	namespace Logging{

typedef enum
{
	Log_Error = 1,
	Log_Warning = 2,
	Log_Info = 4,
} LogStatus;

}}

#endif /* LOGSTATUS_H_ */
