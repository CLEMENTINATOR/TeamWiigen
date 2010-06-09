#include <ogcsys.h>
#include <libutils/exception/Exception.h>
#include <libutils/Xml.h>
#include <libutils/fs/Device.h>
#include <libutils/ui/UIManager.hpp>
#include <libutils/fs/Directory.h>
#include <iostream>

#include <wiiuse/wpad.h>
#include "Tools.h"
#include "Sciifii.h"
#include "Config.h"
#include "ui/MainMenu.h"
#include "ui/AdvancedMenu.h"
#include "ui/Disclaimer.h"
#include "ui/GraphicDisclaimer.h"

#include <cstdlib>
#include <unistd.h>

#include <libutils/logging/GeckoLogger.h>
#include <libutils/logging/FileLogger.h>

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

    WPAD_Init();
	PAD_Init();
	
    try
    {
    	/*Log::WriteLog(Log_Info,"test",0);*/
        Config::Initialize();
    }
    catch (Exception &ex)
    {
        cout << endl << "\x1b[33m" << "Exception " << ex.GetCode() << endl
        << ex.GetMessage() << "\x1b[37m" << endl
        << "Press A to reboot the wii and relaunch sciifii.";
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
    WPAD_Shutdown();

    try
    {
        Sciifii sci;
        WPAD_Shutdown();
        if (sci.Prepare())
        {
            sci.Execute();
            cout << "Installation done! Press A to reboot the wii.";
        }
        else
            cout <<endl<< "An error occured. Press A to reboot the wii.";
    }
    catch (Exception &ex)
    {
        cout << endl << "\x1b[33m" << "Exception " << ex.GetCode() << endl
        << ex.GetMessage() << "\x1b[37m" << endl
        << "Press A to reboot the wii and relaunch sciifii.";
    }
    catch (...)
    {
        cout << "Unexpected Exception!" << endl
        << "Press A to reboot the wii and relaunch sciifii.";
    }
	
    WPAD_Init();
    Pause();
    //STM_RebootSystem();
	return 0;
}


int main(int argc, char **argv)
{
/*FileLogger l("sd:/log.test");
Log::AddLogProvider(Log_Info,&l);*/
	#ifdef USE_ADVANCED_UI
	return mainUI(argc, argv);
	#else
	return mainText(argc, argv);
	#endif
}

