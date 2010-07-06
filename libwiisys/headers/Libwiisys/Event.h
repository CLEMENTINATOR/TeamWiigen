#ifndef _EVENT_H_
#define _EVENT_H_

#include "Object.h"
#include "EventArgs.h"
#include <fastdelegate.h>
#include <list>

namespace Libwiisys {

/*! \class Event
 * \brief This is the base class of all events
 *
 * You can use it with fastdelegate.
 * Code is like this:
 * myObject.MyEvent += MakeDelegate(myListenerClass, ListenerClassType.myListenerMethod);
 */
class Event : public Object
{
public:
	typedef fastdelegate::FastDelegate2<Object*,EventArgs*> DelegateType;
	virtual void operator()(Object* sender, EventArgs* args);
	virtual void operator+= (DelegateType listener);
	virtual void operator-= (DelegateType listener);
private:
	std::list<DelegateType> listenerList;  // pointer to object
};

}

#endif
