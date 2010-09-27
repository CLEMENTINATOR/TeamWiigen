#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <malloc.h>

/** \namespace Libwiisys
 *
 * \brief Contains all base objects.
 *
 * These objects are used over all our codes and generally are c files or base classes.
 */

namespace Libwiisys {

/**
 * \class Object
 * \brief This is the base class of all classes of libwiisys.
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * This class is empty. It's just used as a base class.
 */
class Object
{
public:
	virtual ~Object() = 0;
	virtual std::string GetType();
	virtual std::string ToString();
	friend std::ostream& operator<< ( std::ostream& theStream, Object& obj );
};

}

#endif
