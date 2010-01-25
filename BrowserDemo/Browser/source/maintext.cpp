#include <iostream>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <string.h>
//#include <debug.h>
#include "UI/TextMode/DirectoryViewer.h"
#include <libutils/system/Identification.h>

using namespace std;

static void *xfb = NULL;
static GXRModeObj *vmode = NULL;

//---------------------------------------------------------------------------------
int maintext(int argc, char **argv)
{
//---------------------------------------------------------------------------------

    IOS_ReloadIOS(249);

    // Initialise the video system
    VIDEO_Init();

    vmode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(vmode));

    VIDEO_Configure(vmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(false);
    VIDEO_Flush();

    VIDEO_WaitVSync();
    if (vmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    int x = 20, y = 20, w, h;
    w = vmode->fbWidth - (x * 2);
    h = vmode->xfbHeight - (y + 20);

    // Initialize the console
    CON_InitEx(vmode, x, y, w, h);


    VIDEO_ClearFrameBuffer(vmode, xfb, COLOR_BLACK);


  // DEBUG_Init(GDBSTUB_DEVICE_WIFI, 8000);

   //  _break();
    // This function initialises the attached controllers
    WPAD_Init();

    // To see the first phrase :)
    cout << "\x1b[2;0H";
    Identification::IdentifyAs(UserType_SU);

	try
	{
		DirectoryViewer viewer;
		viewer.Show();
	}
	catch (Exception &ex)
	{
		cout << endl << "Exception: " << ex.GetMessage();

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
	catch (...)
	{
		cout << endl << "Exception non prévue";
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

    exit(0);
}

