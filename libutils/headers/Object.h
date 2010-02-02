#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <malloc.h>
#include <iostream>

#define M1 mi1 = mallinfo()
#define MINIT mallinfo();\
std::cout << "used space: " << mi2.uordblks + mi2.usmblks << std::endl
#define M2(x) mi1 = mi2; mi2 = mallinfo();\
std::cout << std::endl << (x) << " consumed " << mi2.uordblks + mi2.usmblks - mi1.uordblks - mi1.usmblks << std::endl \
	 << "used space: " << mi2.uordblks + mi2.usmblks << std::endl;

class Object
{
public:
	virtual ~Object() = 0;
};

#endif
