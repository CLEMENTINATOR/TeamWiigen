#include <libwiisys.h>

using namespace Libwiisys;

/*! \brief This execute the event.
 * \param sender The source of the event
 * \param args Additional informations useful to the listeners
 *
 * All listener will be executed.
 */
void Event::operator()(Object* sender, EventArgs* args)
{
	for(std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
		if(*ite != NULL)
			(*ite)(sender, args);
}

/*! \brief Add a listener to the event
 * \param listener The listener to add
 *
 * A listener can be added twice. The second will be executed too.
 */
void Event::operator+= (DelegateType listener)
{
	listenerList.push_back(listener);
}

/*! \brief Remove the listener from the listener list
 * \param listener The listener to remove
 */
void Event::operator-= (DelegateType listener)
{
	listenerList.remove(listener);
}
