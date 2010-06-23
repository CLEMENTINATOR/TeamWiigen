#ifndef LOGTYPE_H_
#define LOGTYPE_H_

namespace Libwiisys {
	namespace Logging{

typedef enum
{
	Lgt_Error = 1,
	Lgt_Warning = 2,
	Lgt_Info = 4,
	Lgt_All = 7,
} LogType;

}}

#endif /* LOGTYPE_H_ */
