#include <libwiisys/system/Event/TitleEvent.h>

using namespace Libwiisys::System::Event;

void TitleEvent::operator()(Object* sender, TitleEventArgs* args)
{
  for (std::list<DelegateType>::iterator ite = listenerList.begin(); ite
       != listenerList.end(); ite++)
    if (*ite != NULL)
      (*ite)(sender, args);
}

void TitleEvent::operator+=(DelegateType listener)
{
  listenerList.push_back(listener);
}

void TitleEvent::operator-=(DelegateType listener)
{
  listenerList.remove(listener);
}


std::string TitleEvent::GetType()
{
  return "Libwiisys::System::Event::TitleEvent;"+Object::GetType();
}
