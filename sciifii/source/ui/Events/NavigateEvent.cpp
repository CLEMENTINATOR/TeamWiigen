#include <sciifii/ui/Events/NavigateEvent.h>

using namespace Libwiisys;

void NavigateEvent::operator()(Object* sender, NavigateEventArgs* args)
{
  for (std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
    if (*ite != NULL)
      (*ite)(sender, args);
}

void NavigateEvent::operator+=(DelegateType listener)
{
  listenerList.push_back(listener);
}

void NavigateEvent::operator-=(DelegateType listener)
{
  listenerList.remove(listener);
}
