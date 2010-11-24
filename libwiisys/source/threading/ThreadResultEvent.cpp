#include <Libwiisys/threading/ThreadResultEvent.h>

using namespace Libwiisys::Threading;

void ThreadResultEvent::operator()(Object* sender, ThreadResultEventArgs* args)
{
  for (std::list<DelegateType>::iterator ite = listenerList.begin(); ite
       != listenerList.end(); ite++)
    if (*ite != NULL)
      (*ite)(sender, args);
}

void ThreadResultEvent::operator+=(DelegateType listener)
{
  listenerList.push_back(listener);
}

void ThreadResultEvent::operator-=(DelegateType listener)
{
  listenerList.remove(listener);
}
