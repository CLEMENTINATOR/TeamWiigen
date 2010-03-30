#include <ui/UIManager.hpp>

#include <wiiuse/wpad.h>

#include <ui/video.h>
#include <ui/audio.h>

#include <ui/Device/PadControllers.hpp>
#include <ui/Resources/ImageResourceManager.hpp>

using namespace UI;
using namespace UI::Component;
using namespace UI::Device;
using namespace UI::Resources;

UIManager::UIManager()
: _uiThread(-1),
  _uiThreadDefined(false)
{
	LWP_MutexInit(&_messageQueueMutex, true);
	
	PAD_Init();
	WPAD_Init();
	InitVideo(); // Initialise video
	InitAudio(); // Initialize audio
	
	// read wiimote accelerometer and IR data
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(WPAD_CHAN_ALL, screenwidth, screenheight);
}

void UIManager::AddMessage(Message* message)
{
	LWP_MutexLock(Current()._messageQueueMutex);
	Current()._messageQueue.push(message);
	LWP_MutexUnlock(Current()._messageQueueMutex);
}

UIManager& UIManager::Current()
{
	static UIManager uiManager;
	return uiManager;
}

bool UIManager::IsUiThread()
{
	if(!Current()._uiThreadDefined)
		return false;
	else 
		return Current()._uiThread == LWP_GetSelf();
}

void UIManager::Run(Form &form)
{
	Current()._uiThread = LWP_GetSelf();
	Current()._uiThreadDefined = true;
	Current()._rootElement = &form;
	form.SetRoot(true);
	form.InitializeComponents();
	
	while(form.Visible())
	{
		Current().Update();
		LWP_YieldThread();
	}
}

void UIManager::Update()
{
	//On lance l'affichage
	Current()._rootElement->StartDrawing();
	
	for(int i= PadController::NumberOfDefinedCursors() - 1; i >= 0; i--)
    {
		PadController& controler = PadController::Currents()[i];
			
		if(controler.wpad.ir.valid)
			Menu_DrawImg(controler.wpad.ir.x- controler.offsetLeft, controler.wpad.ir.y - controler.offsetTop, 96, 96, ImageResourceManager::Get(controler.padImage)->Image(), controler.wpad.ir.angle, 1, 1, 255);
    }
	
	//On affiche toutes les modifications graphiques
	Menu_Render();
	
	//Gestion des input
	for(int i= PadController::NumberOfDefinedCursors() - 1; i >= 0; i--)
	{
		Current()._rootElement->ProcessInput(PadController::Currents()[i]);
	}
	
	//Gestion des messages
	LWP_MutexLock(Current()._messageQueueMutex);
	while(!Current()._messageQueue.empty())
	{
		Message *message = Current()._messageQueue.front();
		Current()._messageQueue.pop();
		Current()._rootElement->ProcessMessage(*message);
		delete message;
	}
	LWP_MutexUnlock(Current()._messageQueueMutex);
}

UIManager::~UIManager()
{
	LWP_MutexDestroy(_messageQueueMutex);
}
