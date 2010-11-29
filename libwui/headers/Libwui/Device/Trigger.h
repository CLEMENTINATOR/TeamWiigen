#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include <string>
#include "../Component/Button.hpp"

namespace Libwui
{
  namespace Device
  {
		class Trigger : public Libwiisys::Object
		{			
		public:
			Trigger(Libwui::Component::Button& item, u32 buttonList);
			void Trig(PadController& controller, std::string rootElementId);
			
			u32 ButtonFlags;
			Libwui::Component::Button* TriggeredItem;
		};
	}
}

#endif