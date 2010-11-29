#include <Libwui/Device/Trigger.h>

using namespace std;
using namespace Libwui::Device;
using namespace Libwui::Component;

Trigger::Trigger(Button& item, u32 buttonList)
  : ButtonFlags(buttonList),
		TriggeredItem(&item)
{}

void Trigger::Trig(PadController& controller, string rootElementId)
{
  if((controller.wpad.btns_u & ButtonFlags) != 0  && TriggeredItem->Visible() && TriggeredItem->IsInUITree())
		TriggeredItem->ProcessTrigger(controller, rootElementId);
}