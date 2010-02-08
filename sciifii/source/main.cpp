#include <ogcsys.h>
#include <libutils/exception/Exception.h>
#include <libutils/fs/Device.h>
#include <iostream>

#include <wiiuse/wpad.h>
#include "Tools.h"
#include "Sciifii.h"
#include "Config.h"
#include "ui/MainMenu.h"
#include "ui/AdvancedMenu.h"
#include "ui/Disclaimer.h"

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

  WPAD_Init();
  
  MainMenu menu;
  MainMenuResult result = menu.Show();
  
  if(result == mmResult_Exit)
	exit(0);
	
  bool uninstall = (result == mmResult_Unhack ? true : false);

  if(!uninstall)
  {
	AdvancedMenu aMenu;
	AdvancedMenuResult aresult = aMenu.Show();
	if(aresult == amResult_Exit)
		exit(0);
  }
  
  Config::CreateUpdateList(uninstall);
  
  Disclaimer::Show();
  
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
	  WPAD_Shutdown();
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

  cout << "This application will reboot in 3 seconds!";
  sleep(3);
  STM_RebootSystem();
}
