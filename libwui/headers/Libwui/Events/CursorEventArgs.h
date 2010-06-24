#ifndef _UI_EVENTS_CURSOREVENTARGS_H_
#define _UI_EVENTS_CURSOREVENTARGS_H_

#include <libwiisys.h>

#include "../Device/PadControllers.hpp"

namespace Libwui
{
	namespace Events
	{
		class CursorEventArgs : public Libwiisys::EventArgs
		{
		private:
			Libwui::Device::PadController *pad;
		public:
			CursorEventArgs(Libwui::Device::PadController& controller);
			Libwui::Device::PadController& Controller();
		};
	}
}
#endif
