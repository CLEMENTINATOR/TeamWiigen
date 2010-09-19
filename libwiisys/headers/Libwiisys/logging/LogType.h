#ifndef LOGTYPE_H_
#define LOGTYPE_H_

namespace Libwiisys {
	namespace Logging {

		/**
		 * @enum LogType
		 * @brief Differents types of opening logs
		 */
		typedef enum
		{
			Lgt_Error = 1, //!< Lgt_Error
			Lgt_Warning = 2,//!< Lgt_Warning
			Lgt_Info = 4, //!< Lgt_Info
			Lgt_All = 7, //!< Lgt_All
			Lgt_Debug = 8,
		}LogType;

	}}

#endif /* LOGTYPE_H_ */
