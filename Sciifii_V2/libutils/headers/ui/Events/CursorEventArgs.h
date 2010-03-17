#ifndef _UI_EVENTS_CURSOREVENTARGS_H_
#define _UI_EVENTS_CURSOREVENTARGS_H_

#include "../../events/EventArgs.h"
#include "../Device/PadControllers.hpp"

namespace UI
{
	namespace Events
	{
		class CursorEventArgs : public EventArgs
		{
		private:
			UI::Device::PadController *pad;
		public:
			CursorEventArgs(UI::Device::PadController& controller);
			UI::Device::PadController& Controller();
		};
	}
}
#endif