#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <malloc.h>

namespace Libwiisys {

/*! \class Object
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
};

}

#endif
