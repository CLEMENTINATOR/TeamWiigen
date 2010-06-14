#include <ogcsys.h>
#include <libutils/exception/Exception.h>
#include <libutils/Xml.h>
#include <libutils/fs/Device.h>
#include <libutils/ui/UIManager.hpp>
#include <libutils/fs/Directory.h>
#include <libutils/system/Title.h>
#include <iostream>

#include "Tools.h"
#include "Sciifii.h"
#include "Config.h"
#include "ui/MainMenu.h"
#include "ui/AdvancedMenu.h"
#include "ui/Disclaimer.h"
#include "ui/GraphicDisclaimer.h"
#include "ui/VirtualPad.h"

#include <cstdlib>
#include <unistd.h>
#include <sstream>

#include <libutils/logging/Log.h>

//#define USE_ADVANCED_UI

using namespace std;
using namespace UI;
using namespace UI::Component;
using namespace UI::Device;

static void *xfb;
static GXRModeObj *vmode;

int mainUI(int argc, char **argv)
{
    Config::Initialize();
    GraphicDisclaimer g;
    PadController::LoadCursorImages(0, "sd:/sciifii/default/cursor.png", 48, 48);
	UIManager::Run(g);
	STM_RebootSystem();
	return 0;
}

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
    Title::ReloadIOS(36);
    VPAD_Init();
    Pause();
	return 0;
}


int main(int argc, char **argv)
{
    Log::Init("sciifii", SCIIFII_VERSION);
	#ifdef USE_ADVANCED_UI
	return mainUI(argc, argv);
	#else
	return mainText(argc, argv);
	#endif
}

