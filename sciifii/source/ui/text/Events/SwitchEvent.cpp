#include <Sciifii.h>

using namespace Libwiisys;

void SwitchEvent::operator()(Object* sender, SwitchEventArgs* args) {
	for (std::list<DelegateType>::iterator ite = listenerList.begin(); ite
			!= listenerList.end(); ite++)
		if (*ite != NULL)
			(*ite)(sender, args);
}

void SwitchEvent::operator+=(DelegateType listener) {
	listenerList.push_back(listener);
}

void SwitchEvent::operator-=(DelegateType listener) {
	listenerList.remove(listener);
}