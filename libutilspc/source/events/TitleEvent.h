#ifndef _TITLE_EVENT_H_
#define _TITLE_EVENT_H_

#include "../Object.h"
#include "TitleEventArgs.h"
#include <fastdelegate.h>
#include <list>

class TitleEvent : public Object
{
public:
	typedef fastdelegate::FastDelegate2<Object*,TitleEventArgs*> DelegateType;
	virtual void operator()(Object* sender, TitleEventArgs* args);
	virtual void operator+= (DelegateType listener);
	virtual void operator-= (DelegateType listener);
private:
	std::list<DelegateType> listenerList;  // pointer to object
};

#endif
