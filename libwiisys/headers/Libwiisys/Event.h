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
		/** Little typedef */
		typedef fastdelegate::FastDelegate2<Object*,EventArgs*> DelegateType;

		/*! \brief This execute the event.
		 * \param sender The source of the event
		 * \param args Additional informations useful to the listeners
		 *
		 * All listener will be executed.
		 */
		virtual void operator()(Object* sender, EventArgs* args);

		/*!
		 * \brief Add a listener to the event
		 * \param listener The listener to add
		 *
		 * A listener can be added twice. The second will be executed too.
		 */
		virtual void operator+= (DelegateType listener);

		/*!
		 * \brief Remove the listener from the listener list
		 * \param listener The listener to remove
		 */
		virtual void operator-= (DelegateType listener);
	private:
		std::list<DelegateType> listenerList; // pointer to object
	};

}

#endif
