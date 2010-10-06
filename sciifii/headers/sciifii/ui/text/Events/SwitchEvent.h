#ifndef _SWITCH_EVENT_H_
#define _SWITCH_EVENT_H_

#include <FastDelegate.h>
#include <list>
#include "SwitchEventArgs.h"

class SwitchEvent : public Libwiisys::Object
{
public:

	/** Little typedef for a more readable code*/
	typedef fastdelegate::FastDelegate2<Object*,SwitchEventArgs*> DelegateType;

	/*!
	 * \brief This execute the event.
	 * \param sender The source of the event
	 * \param args Additional informations useful to the listeners
	 *
	 * All listener will be executed.
	 */
	virtual void operator()(Object* sender, SwitchEventArgs* args);

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

#endif
