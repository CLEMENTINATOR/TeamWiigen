#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <malloc.h>
#include "debug_utils.h"
#include <sstream>

#define M1 mi1 = mallinfo();\

#define MINIT mallinfo();\
std::stringstream debug_message;\
debug_message << "used space: " << mi2.uordblks + mi2.usmblks << std::endl;\
dbprintf(debug_message.str())

#define M2(x) mi1 = mi2; mi2 = mallinfo();\
debug_message << std::endl << (x) << " consumed " << mi2.uordblks + mi2.usmblks - mi1.uordblks - mi1.usmblks << std::endl \
			  << "used space: " << mi2.uordblks + mi2.usmblks << std::endl;\
dbprintf(debug_message.str())

class Object
{
public:
	virtual ~Object() = 0;
};

#endif
