#include <libwui/UIManager.hpp>
#include <libwui/video.h>
#include <libwui/audio.h>
#include <wiiuse/wpad.h>
#include <Libwui/Resources/ImageResourceManager.hpp>


using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace Libwui::Resources;

UIManager::UIManager()
    : _uiThread(-1),
    _uiThreadDefined(false),
    _rootElement(NULL),
    _modalDialog(NULL)
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

void UIManager::ShowDialog(Libwui::Component::Form& dialog)
{
  Current()._modalDialog = &dialog;
  dialog.SetRoot(true);
  dialog.InitializeComponents();

  while(dialog.Visible())
  {
    Current().Update();
    LWP_YieldThread();
  }

  Current()._modalDialog = NULL;
  dialog.SetRoot(false);
}

void UIManager::Update()
{
  //draw root
  Current()._rootElement->StartDrawing();

  //then draw dialog if their is one
  if(Current()._modalDialog)
    Current()._modalDialog->StartDrawing();

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
    if(Current()._modalDialog)
      Current()._modalDialog->ProcessInput(PadController::Currents()[i]);
    else
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
