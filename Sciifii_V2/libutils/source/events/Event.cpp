#include <events/Event.h>

void Event::operator()(Object* sender, EventArgs* args)
{
	for(std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
		if(*ite != NULL)
			(*ite)(sender, args);
}

void Event::operator+= (DelegateType listener)
{
	listenerList.push_back(listener);
}

void Event::operator-= (DelegateType listener)
{
	listenerList.remove(listener);
}
