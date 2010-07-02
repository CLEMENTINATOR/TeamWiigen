#ifndef FILEMODE_H_
#define FILEMODE_H_

namespace Libwiisys {	namespace IO {

/**
 *\enum FileMode
 *\brief Represents some file modes access
 **/
typedef enum
		{
	/** R */
	FileMode_Read,
	/** W */
	FileMode_Write,
	/** RW */
	FileMode_ReadWrite,
		} FileMode;

}}

#endif /* FILEMODE_H_ */
