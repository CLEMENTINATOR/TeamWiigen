#include <Libwiisys/threading/ProgressEvent.h>

using namespace Libwiisys::Threading;

void ProgressEvent::operator()(Object* sender, ProgressEventArgs* args)
{
  for(std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
    if(*ite != NULL)
      (*ite)(sender, args);
}

void ProgressEvent::operator+= (DelegateType listener)
{
  listenerList.push_back(listener);
}

void ProgressEvent::operator-= (DelegateType listener)
{
  listenerList.remove(listener);
}
