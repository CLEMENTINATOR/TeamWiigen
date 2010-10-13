#ifndef _THREAD_RESULT_EVENT_H_
#define _THREAD_RESULT_EVENT_H_

#include "../Object.h"
#include "ThreadResultEventArgs.h"
#include <FastDelegate.h>
#include <list>

namespace Libwiisys {namespace Threading {
	/**
	 * \class TitleEvent
	 * \brief Events used in Title Installation
	 * \see TitleEventArgs
	 */
	class ThreadResultEvent : public Object
	{
	public:
						
		/** Little typedef for a more readable code*/
		typedef fastdelegate::FastDelegate2<Object*,ThreadResultEventArgs*> DelegateType;

		/*!
		 * \brief This execute the event.
		 * \param sender The source of the event
		 * \param args Additional informations useful to the listeners
		 *
		 * All listener will be executed.
		 */
		virtual void operator()(Object* sender, ThreadResultEventArgs* args);

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

}}

#endif
