#ifndef _UI_DEVICE_PADCONTROLLERS_
#define _UI_DEVICE_PADCONTROLLERS_

#include "../../Object.h"
#include <wiiuse/wpad.h>
#include <string>

namespace UI
{
	namespace Device
	{
		typedef struct _paddata 
		{
			u16 btns_d;
			u16 btns_u;
			u16 btns_h;
			s8 stickX;
			s8 stickY;
			s8 substickX;
			s8 substickY;
			u8 triggerL;
			u8 triggerR;
		} PADData;
		
		class PadController : public Libwiisys::Object
		{		
		private:
			bool enabled;
			PadController();
		public:
			static PadController* Currents();
			static void LoadCursorImages(int channel, const std::string& im, int offsetLeft, int offsetTop);
			static int NumberOfDefinedCursors();
			std::string padImage;
			int offsetLeft;
			int offsetTop;
			s32 chan; //!< Trigger controller channel (0-3, -1 for all)
			s32 btns_c;
			WPADData wpad; //!< Wii controller trigger data
			PADData pad; //!< GameCube controller trigger data
		};
	}
}

#endif
