#include <wiiuse/wpad.h>
#include "MenuBase.h"

MenuBase::MenuBase()
  : cursorPosition(0),
	nbItems(0),
	skip(0),
	skipMax(0)
{}

u32 MenuBase::GetCommand()
{
	while (1)
	{
		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 pressed = WPAD_ButtonsDown(0);

		// We return to the main programme
		if (pressed)
			return pressed;

		// Wait for the next frame
		VIDEO_WaitVSync();
	}
}
