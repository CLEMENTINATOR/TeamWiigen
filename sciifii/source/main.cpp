#include <ogcsys.h>
#include <libwiisys.h>

#include <iostream>

#include "Tools.h"
#include "Sciifii.h"
#include "Config.h"

#include <cstdlib>
#include <unistd.h>
#include <sstream>


//#define USE_ADVANCED_UI

using namespace std;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Logging;


#ifdef USE_ADVANCED_UI

#include <libwui.h>
#include "ui/GraphicDisclaimer.h"

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;

int mainUI(int argc, char **argv)
{
  Config::Initialize();
  GraphicDisclaimer g;
  PadController::LoadCursorImages(0, "sd:/sciifii/default/cursor.png", 48, 48);
	UIManager::Run(g);
	STM_RebootSystem();
	return 0;
}

#else

#include "ui/MainMenu.h"
#include "ui/AdvancedMenu.h"
#include "ui/Disclaimer.h"
#include "ui/VirtualPad.h"

static void *xfb;
static GXRModeObj *vmode;

int mainText(int argc, char **argv)
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

    VPAD_Init();

    try
    {
        Config::Initialize();
    }
    catch (Exception &ex)
    {
        cout << endl << "\x1b[33m" << "Exception " << ex.GetCode() << endl
        << ex.GetMessage() << "\x1b[37m" << endl
        << "Press A to exit and relaunch sciifii.";
        stringstream str;
        str<<"Exception "<<ex.GetMessage()<<" "<<ex.GetCode()<<" in : "<<Sciifii::LastStepMessage();
        Log::WriteLog(Log_Error,str.str());
        Pause();
        return 0;
    }

    MainMenu menu;
    MainMenuResult result = menu.Show();

    if (result == mmResult_Exit)
       return 0;

    if (result == mmResult_Advanced)
    {
        AdvancedMenu aMenu;
        AdvancedMenuResult aresult = aMenu.Show();
        if (aresult == amResult_Exit)
           return 0;
    }
    Config::ValidateOptions();
    Disclaimer::Show();
    VPAD_Shutdown();

    try
    {
        Sciifii sci;
        if (sci.Prepare())
        {
            sci.Execute();
            cout << "Installation done! Press A to exit.";
        }
        else
        {
        	Log::WriteLog(Log_Error,Sciifii::LastStepMessage());
        	throw Exception("An error occured during prepare.",-1);
        }
    }
    catch (Exception &ex)
    {
        cout << endl << "\x1b[33m" << "Exception " << ex.GetCode() << endl
        << ex.GetMessage() << "\x1b[37m" << endl
        << "Press A to exit and relaunch sciifii.";

        stringstream str;
        str<<"Exception "<<ex.GetMessage()<<" "<<ex.GetCode()<<" in : "<<Sciifii::LastStepMessage();
        Log::WriteLog(Log_Error,str.str());
    }
    catch (...)
    {
        cout << "Unexpected Exception!" << endl
        << "Press A to exit and relaunch sciifii.";

        Log::WriteLog(Log_Error,"UnHandled Exception ! "+Sciifii::LastStepMessage());
    }
    VPAD_Init();
    Pause();
	return 0;
}

#endif

int main(int argc, char **argv)
{
    Log::Init("sciifii", SCIIFII_VERSION);
	#ifdef USE_ADVANCED_UI
	return mainUI(argc, argv);
	#else
	return mainText(argc, argv);
	#endif
}

