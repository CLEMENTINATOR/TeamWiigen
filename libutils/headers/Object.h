#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <malloc.h>
#include "debug_utils.h"
#include <sstream>
#include <iostream>

#define M1 mi1 = mallinfo();\

#define MINIT struct mallinfo mi1, mi2;\
mi1 = mallinfo();\
std::cout << "used space: " << mi1.uordblks + mi1.usmblks << std::endl

#define M2(x) mi2 = mallinfo();\
cout << std::endl << (x) << " consumed " << mi2.uordblks + mi2.usmblks - mi1.uordblks - mi1.usmblks << std::endl \
			  << "used space: " << mi2.uordblks + mi2.usmblks << std::endl

class Object
{
public:
	virtual ~Object() = 0;
};

#endif
