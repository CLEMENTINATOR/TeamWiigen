#include <libwui.h>

using namespace Libwui::Events;

void CursorEvent::operator()(Object* sender, CursorEventArgs* args)
{
	for(std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
		if(*ite != NULL)
			(*ite)(sender, args);
}

void CursorEvent::operator+= (DelegateType listener)
{
	listenerList.push_back(listener);
}

void CursorEvent::operator-= (DelegateType listener)
{
	listenerList.remove(listener);
}
