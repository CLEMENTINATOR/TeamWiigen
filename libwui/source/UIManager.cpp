#include <Libwui/UIManager.hpp>
#include <Libwui/video.h>
#include <Libwui/audio.h>
#include <wiiuse/wpad.h>
#include <Libwui/Resources/ImageResourceManager.hpp>
#include <Libwui/Resources/ResourceManager.h>

using namespace std;
using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace Libwui::Resources;

UIManager::UIManager()
    : _uiThread(-1),
    _uiThreadDefined(false),
    _rootElement(NULL),
    _untilNextCacheClean(20)
{
  LWP_MutexInit(&_messageQueueMutex, false);

  InitVideo(); // Initialise video
  InitAudio(); // Initialize audio

  TrackWPads(true);
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
	form.SetId("root");
  form.InitializeComponents();

  while(form.Visible())
  {
    Current().Update();
    LWP_YieldThread();
  }

	form.SetId("");
  Current()._uiThreadDefined = false;
  Current()._rootElement = NULL;
}

void UIManager::ShowDialog(Libwui::Component::Form& dialog)
{
  Current()._dialogs.push_back(&dialog);
  dialog.MakeModal(Current()._rootElement);
  dialog.SetRoot(true);
	stringstream id;
	id << "dialog" << Current()._dialogs.size();
	dialog.SetId(id.str());
	dialog.InitializeComponents();
	
  while(dialog.Visible())
  {
    Current().Update();
    LWP_YieldThread();
  }

	dialog.SetId("");
	dialog.SetRoot(false);
  dialog.MakeModal(NULL);
  Current()._dialogs.pop_back();
}

void UIManager::Update()
{
  //draw root
  Current()._rootElement->StartDrawing();

  //then draw dialog if their is one
  for(vector<Form*>::iterator f = Current()._dialogs.begin(); f!= Current()._dialogs.end(); f++)
    (*f)->StartDrawing();

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
    //Disable the root if a modalDialog is opened
    if(!Current()._dialogs.empty())
    	Current()._dialogs.back()->ProcessInput(PadController::Currents()[i]);
    else
      Current()._rootElement->ProcessInput(PadController::Currents()[i]);
			
		//Gestion des trigger
		if(!Current()._dialogs.empty())
			for(vector<Trigger>::iterator ite = _triggers.begin(); ite != _triggers.end(); ite++)
				ite->Trig(PadController::Currents()[i], Current()._dialogs.back()->UniqueId());
		else
			for(vector<Trigger>::iterator ite = _triggers.begin(); ite != _triggers.end(); ite++)
				ite->Trig(PadController::Currents()[i], Current()._rootElement->UniqueId());
  }

  //Gestion des messages
  LWP_MutexLock(Current()._messageQueueMutex);
  while(!Current()._messageQueue.empty())
  {
    Message *message = Current()._messageQueue.front();
    Current()._messageQueue.pop();

    if(!Current()._dialogs.empty())
      Current()._dialogs.back()->ProcessMessage(*message);
    else
      Current()._rootElement->ProcessMessage(*message);
    delete message;
  }
  LWP_MutexUnlock(Current()._messageQueueMutex);

  if(_untilNextCacheClean++ == 100)
  {
	  _untilNextCacheClean = 0;
	  ResourceManager::Clean();
  }
}

void UIManager::TrackWPads(bool track)
{
  if(!track)
    Menu_StopWPads();
  else
    Menu_StartWPads();
}

UIManager::~UIManager()
{
  LWP_MutexDestroy(_messageQueueMutex);
}

void UIManager::SetTrigger(Button& item, u32 flag)
{
	vector<Trigger>::iterator currentTrigger;
	for(currentTrigger = Current()._triggers.begin(); currentTrigger != Current()._triggers.end(); currentTrigger++)
		if(currentTrigger->TriggeredItem == &item)
			break;
		
	if(flag == 0)
	{
		if(currentTrigger != Current()._triggers.end())
			Current()._triggers.erase(currentTrigger);
		return;
	}
	
	if(currentTrigger != Current()._triggers.end())
		currentTrigger->ButtonFlags = flag;
	else
	{
		Trigger t(item, flag);
		Current()._triggers.push_back(t);
	}
	
}