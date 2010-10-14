#include <libwiisys/threading/DoWorkEvent.h>

using namespace Libwiisys::Threading;

void DoWorkEvent::operator()(Object* sender, Object* args)
{
  for (std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
    if (*ite != NULL)
      (*ite)(sender, args);
}

void DoWorkEvent::operator+= (DelegateType listener)
{
  listenerList.push_back(listener);
}

void DoWorkEvent::operator-= (DelegateType listener)
{
  listenerList.remove(listener);
}
