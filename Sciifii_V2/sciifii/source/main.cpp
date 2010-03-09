#include <ogcsys.h>
#include <libutils/exception/Exception.h>
#include <libutils/Xml.h>
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

    Device::Mount("sd:/");
    try
    {
        Config::Initialize();
    }
    catch (Exception &ex)
    {
        cout << endl << "\x1b[33m" << "Exception " << ex.GetCode() << endl
        << ex.GetMessage() << "\x1b[37m" << endl
        << "Press A to reboot the wii and relaunch sciifii.";
        Pause();
        STM_RebootSystem();
    }

    MainMenu menu;
    MainMenuResult result = menu.Show();

    if (result == mmResult_Exit)
        STM_RebootSystem();

    if (result == mmResult_Advanced)
    {
        AdvancedMenu aMenu;
        AdvancedMenuResult aresult = aMenu.Show();
        if (aresult == amResult_Exit)
            STM_RebootSystem();
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
            Device::UnMount("sd:/");
            cout << "Installation done! Press A to reboot the wii.";
        }
        else
            cout << "An error occured. Press A to reboot the wii.";
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
    STM_RebootSystem();
}
