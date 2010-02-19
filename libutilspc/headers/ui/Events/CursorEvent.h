#ifndef _UI_EVENTS_CURSOREVENT_H_
#define _UI_EVENTS_CURSOREVENT_H_

#include "../../Object.h"
#include "CursorEventArgs.h"
#include <list>
#include <fastdelegate.h>

namespace UI
{
	namespace Events
	{
		class CursorEvent : public Object
		{
		public:
			typedef fastdelegate::FastDelegate2<Object*,CursorEventArgs*> DelegateType;
			virtual void operator()(Object* sender, CursorEventArgs* args);
			virtual void operator+= (DelegateType listener);
			virtual void operator-= (DelegateType listener);
		private:
			std::list<DelegateType> listenerList;  // pointer to object
		};
	}
}

#endif
