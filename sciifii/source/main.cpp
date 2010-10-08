#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sstream>

#include <ogcsys.h>
#include <Sciifii.h>

//#define USE_ADVANCED_UI

using namespace std;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Logging;

class IMain
{
public:
	virtual int main(int argc, char **argv) = 0;
};

#ifdef USE_ADVANCED_UI

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;

class MainUI : public IMain
{
	int main(int argc, char **argv)
	{
		string configFile = "sd:/sciifii/config.xml";
		if(argc == 2)
			configFile = string(argv[1]);
			
		Config::Initialize(configFile);
		GraphicDisclaimer g;
		PadController::LoadCursorImages(0, "sd:/sciifii/default/cursor.png", 48, 48);
		UIManager::Run(g);
		STM_RebootSystem();
		return 0;
	}
};

#else

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
				string configFile = "sd:/sciifii/config.xml";
				if(argc == 2)
					configFile = string(argv[1]);
					
				Config::Initialize(configFile);
			}
			catch (Exception &ex)
			{
					cout << endl << "\x1b[33m" << ex << "\x1b[37m" << endl
					<< "Press A to exit and relaunch sciifii.";
					Log::WriteLog(Log_Error,ex.ToString());
					Pause();
					return 0;
			}			

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
			}
			catch (...)
			{
					cout << "Unexpected Exception!" << endl
					<< "Press A to exit and relaunch sciifii.";

					Log::WriteLog(Log_Error,"UnHandled Exception ! "+Sciifii::LastStepMessage());
			}
			Pause();
		return 0;
	}
};
#endif

int main(int argc, char **argv)
{
  Log::Init("sciifii", SCIIFII_VERSION);
	IMain *m = NULL;
	#ifdef USE_ADVANCED_UI
	m = new MainUI();
	#else
	m = new MainText();
	#endif
	return m->main(argc, argv);
}

