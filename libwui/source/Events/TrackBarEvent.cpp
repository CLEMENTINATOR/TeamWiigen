#include <Libwui/Events/TrackBarEvent.hpp>

using namespace Libwui::Events;

void TrackBarEvent::operator()(Object* sender, TrackBarEventArgs* args)
{
  for(std::list<DelegateType>::iterator ite = listenerList.begin(); ite != listenerList.end(); ite++)
    if(*ite != NULL)
      (*ite)(sender, args);
}

void TrackBarEvent::operator+= (DelegateType listener)
{
  listenerList.push_back(listener);
}

void TrackBarEvent::operator-= (DelegateType listener)
{
  listenerList.remove(listener);
}
