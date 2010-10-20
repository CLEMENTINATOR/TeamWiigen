#ifndef _G_MENU_ITEM_H_
#define _G_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Object.h>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Control.hpp>
#include "../../Events/SwitchEvent.h"
#include "../../Events/SwitchEventArgs.h"
#include "../../Events/NavigateEvent.h"
#include "../../Events/NavigateEventArgs.h"

class GMenuItem : public Libwui::Control
{
  protected:
    std::string _text;
    void OnModifySwitch(SwitchEventArgs& args);
    void OnNavigate(NavigateEventArgs& args);

  public:
    bool BreakBefore;
    bool BreakAfter;

    GMenuItem(TiXmlElement* node);
    virtual void Validate();
    virtual void Cancel();

    SwitchEvent SwitchSelectionChanged;
    NavigateEvent NavigateRequested;
};

#endif
