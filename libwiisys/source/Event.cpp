#include <Libwiisys/Event.h>

using namespace Libwiisys;

void Event::operator()(Object* sender, EventArgs* args)
{
  for (std::list<DelegateType>::iterator ite = listenerList.begin(); ite
       != listenerList.end(); ite++)
    if (*ite != NULL)
      (*ite)(sender, args);
}

void Event::operator+=(DelegateType listener)
{
  listenerList.push_back(listener);
}

void Event::operator-=(DelegateType listener)
{
  listenerList.remove(listener);
}

std::string Event::GetType()
{
  return "Libwiisys::Event,"+Object::GetType();
}
