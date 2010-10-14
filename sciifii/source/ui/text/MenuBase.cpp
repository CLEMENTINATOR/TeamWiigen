#include <sciifii/ui/text/MenuBase.h>
#include <sciifii/ui/text/VirtualPad.h>

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
    // Call VPAD_ScanPads each loop, this reads the latest controller states
    VPAD_ScanPads();

    // VPAD_ButtonsDown tells us which buttons were pressed in this loop
    // this is a "one shot" state which will not fire again until the button has been released
    u32 pressed = VPAD_ButtonsDown(0);

    // We return to the main programme
    if (pressed)
      return pressed;

    // Wait for the next frame
    VIDEO_WaitVSync();
  }
}
