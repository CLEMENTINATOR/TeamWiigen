#ifndef USERTYPE_H_
#define USERTYPE_H_

/*!
*\enum UserType
*\brief A enum representing some wii users
*/
typedef enum
{
    /** Super User */
	UserType_SU = 0,
	/** System Menu ? */
	UserType_SystemMenu = 1,
    /** Unknown */
	UserType_Unknown = 2,
} UserType;

#endif /* USERTYPE_H_ */
