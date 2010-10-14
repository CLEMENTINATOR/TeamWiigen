#ifndef _I_MENU_ITEM_H_
#define _I_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Object.h>
#include <Libwiisys/Serialization/Xml.h>
#include "../../Events/SwitchEvent.h"
#include "../../Events/SwitchEventArgs.h"
#include "../../Events/NavigateEvent.h"
#include "../../Events/NavigateEventArgs.h"

class IMenuItem
{
  protected:
    std::string _text;
    void OnModifySwitch(SwitchEventArgs& args);
    void OnNavigate(NavigateEventArgs& args);

  public:
    bool Selectable;
    bool Selected;

    IMenuItem(TiXmlElement* node);
    virtual void Validate();
    virtual void Cancel();

    SwitchEvent SwitchSelectionChanged;
    NavigateEvent NavigateRequested;
};

#endif
