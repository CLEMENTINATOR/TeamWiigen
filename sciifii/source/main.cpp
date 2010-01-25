#include <ogcsys.h>
#include <libutils/exception/Exception.h>
#include <libutils/fs/Device.h>
#include <iostream>

#include <wiiuse/wpad.h>
#include "Tools.h"
#include "Sciifii.h"
#include "Config.h"

#include <cstdlib>
#include <unistd.h>

using namespace std;

static void *xfb;
static GXRModeObj *vmode;

int main(int argc, char **argv)
{
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


  cout << endl << endl;

  cout << "Cioscorp online Installer v1 based on cios corp v3.6" << endl
	   << "Made by Arasium, Teton and Fanta." << endl
	   << "Tested by Jicay, JeanMi, Vlad and Thetataz (and many others)." << endl
	   << "Special thanks to Waninkoko for his help" << endl
	   << "Thanks to da_letter_a for the cios corp knowledge." << endl
	   << "mail: TeamWiigen@googlemail.com" << endl << endl
	   << "this app comes with no warranty"<< endl
	   << "so if you don't know what you're doing here, fuck off" << endl;

  /*if(!Ask("(& don't press A as well x))"))
	  exit(0);*/

  try
  {
	  Sciifii sci;
	  Device::Mount("sd:/");
	  if(!sci.Prepare())
	  {
		  cout << "Press a button to exit.";
		  Pause();
		  exit(0);
	  }
	  sci.Execute();
	  Device::UnMount("sd:/");
  }
  catch(Exception &ex)
  {
	cout << endl << "\x1b[33m" << "Exception " << ex.GetCode() << endl
		 << ex.GetMessage() << "\x1b[37m" << endl;
  }
  catch(...)
  {
	cout << "Unexpected Exception";
  }

  cout << "This application will exit, please reboot you wii!";
  WPAD_Init();
  Pause();
  STM_RebootSystem();
}
