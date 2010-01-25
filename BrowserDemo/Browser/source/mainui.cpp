#include <libutils/ui/UIManager.hpp>

#include "UI/GraphicMode/BrowserWindow.h"

using namespace UI;
using namespace UI::Component;
using namespace UI::Device;

int mainui(int argc, char** argv)
{
	BrowserWindow mainForm;
	PadController::LoadCursorImages(0, "sd:/apps/libui/images/icon.png", 48, 48);
	//mainForm.InitializeComponents();
	UIManager::Run(mainForm);

	return 0;
}
