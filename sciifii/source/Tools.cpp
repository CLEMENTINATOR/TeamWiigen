#include "Tools.h"
#include <iostream>
#include <wiiuse/wpad.h>

using namespace std;

void Pause()
{
	while (1)
    {
      // Call WPAD_ScanPads each loop, this reads the latest controller states
      WPAD_ScanPads();

      // WPAD_ButtonsDown tells us which buttons were pressed in this loop
      // this is a "one shot" state which will not fire again until the button has been released
      u32 pressed = WPAD_ButtonsDown(0);

      // We return to the main programme
      if ( pressed & (WPAD_BUTTON_A | WPAD_BUTTON_HOME) )
        break;

      // Wait for the next frame
      VIDEO_WaitVSync();
    }
}

bool Ask(const string& message)
{
	cout << message << endl << "A to accept, any other button to not." << endl;

	bool returnValue = false;;

	while (1)
    {
      // Call WPAD_ScanPads each loop, this reads the latest controller states
      WPAD_ScanPads();

      // WPAD_ButtonsDown tells us which buttons were pressed in this loop
      // this is a "one shot" state which will not fire again until the button has been released
      u32 pressed = WPAD_ButtonsDown(0);

      // We return to the main programme
      if(pressed)
      {
    	  if (pressed & WPAD_BUTTON_A)
    		  returnValue = true;
    	  break;
      }
      // Wait for the next frame
      VIDEO_WaitVSync();
    }

	return returnValue;
}
