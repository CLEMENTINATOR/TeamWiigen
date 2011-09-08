#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <ogcsys.h>
#include <Libwiisys/logging/Log.h>
#include <Libwui/UIManager.hpp>
#include <Libwui/Resources/ThemeManager.hpp>
#include <Libwiisys/Exceptions/AbortException.h>
#include <Libwui/Device/PadControllers.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <sciifii/business/common/ExitSciifiiException.h>
#include <sciifii/ui/text/VirtualPad.h>
#include <sciifii/Tools.h>
#include <sciifii/ui/text/MenuManager.h>
#include <sciifii/Sciifii.h>
#include <sciifii/Config.h>
#include <sciifii/ui/graphic/GDisclaimer.h>
#include <sciifii/ui/graphic/GMenuManager.h>

using namespace std;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Logging;
using namespace Libwui::Resources;
using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;


class IMain
{
  public:
    virtual int main(int argc, char **argv) = 0;
};



class MainUI : public IMain
{
    int main(int argc, char **argv)
    {
      if(Config::ThemeDirectory().size() != 0)
        ThemeManager::ThemeRootFolder(Config::ThemeDirectory());


      GDisclaimer g;
      PadController::LoadCursorImages(0, "cursor.png", 48, 48);

      try
      {
        UIManager::Run(g);
        UIManager::Run(GMenuManager::Instance());
      }
      catch(ExitSciifiiException &ex)
      {}
			catch(Exception &ex)
			{
				MessageBox mb;
				mb.SetTitlePosition(16, 2);
				mb.SetTitleSize(279, 14);
				mb.SetTextPosition(16, 64);
				mb.SetTextSize(279, 45);
				mb.SetButtonPosition(76, 137);
				mb.DefaultButtonImage("go_button.png");
				mb.OverButtonImage("go_button_over.png");
				mb.SetMessageBoxImage("error_popup_screen.png");
				mb.Show( ex.ToString(),  "Exception");
			}

      return 0;
    }
};

static void *xfb;
static GXRModeObj *vmode;

class MainText : public IMain
{
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
      if (vmode->viTVMode & VI_NON_INTERLACE)
        VIDEO_WaitVSync();

      int x = 20, y = 20, w, h;
      w = vmode->fbWidth - (x * 2);
      h = vmode->xfbHeight - (y + 20);

      // Initialize the console
      CON_InitEx(vmode, x, y, w, h);
      VIDEO_ClearFrameBuffer(vmode, xfb, COLOR_BLACK);

      VPAD_Init();

      try
      {
        MenuManager::Instance().DisplayMenu();
      }
      catch (Exception &ex)
      {
         cout << endl << "\x1b[33m" << ex << "\x1b[37m" << endl
        << "Press A to exit and relaunch sciifii.";
		

        stringstream str;
        str<< ex <<" in : "<<Sciifii::LastStepMessage();
        Log::WriteLog(Log_Error,str.str());
		
	   Pause();
      }
      catch (...)
      {
        cout << "Unexpected Exception!" << endl
        << "Press A to exit and relaunch sciifii.";
		
        Log::WriteLog(Log_Error,"UnHandled Exception ! "+Sciifii::LastStepMessage());
	
      Pause();
      }
      
      return 0;
    }
};

int main(int argc, char **argv)
{
  Log::Init("sciifii", SCIIFII_VERSION);
  string configFile = "sd:/sciifii/config.xml";
  if(argc == 2)
    configFile = string(argv[1]);
  Config::Initialize(configFile);
	  
  IMain *m = NULL;
  if(Config::IsUiMode())
	m = new MainUI();
  else
    m = new MainText();

  return m->main(argc, argv);
}

