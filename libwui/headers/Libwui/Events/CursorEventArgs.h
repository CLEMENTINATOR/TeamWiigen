#ifndef _UI_EVENTS_CURSOREVENTARGS_H_
#define _UI_EVENTS_CURSOREVENTARGS_H_

#include "../../EventArgs.h"
#include "../Device/PadControllers.hpp"

namespace UI
{
	namespace Events
	{
		class CursorEventArgs : public Libwiisys::EventArgs
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
