#include <sciifii/ui/graphic/GSciifiiLauncher2.h>
#include <Libwiisys/Exceptions/AbortException.h>
#include <sciifii/Sciifii.h>
#include <Libwiisys/logging/Log.h>
#include <sciifii/ui/text/VirtualPad.h>
#include <Libwui/UIManager.hpp>
#include <Libwui/Resources/Colors.h>
#include <Libwui/video.h>
#include <sstream>
#include <Libwiisys/threading/ThreadResultEvent.h>
#include <Libwiisys/threading/ThreadResultEventArgs.h>
#include <Libwiisys/Exceptions/SystemException.h>

using namespace Libwiisys;
using namespace Libwiisys::Threading;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Logging;
using namespace std;
using namespace fastdelegate;
using namespace Libwui;

void GSciifiiLauncher2::InitializeComponents()
{
  BackgroundColor(Colors::FromRGBA(122, 122, 122, 125));
  SetPosition(0, 0);
  SetSize(640, 480);

  bOk.Enabled(false);
  bOk.Click += MakeDelegate(this, &GSciifiiLauncher2::Exit);
  bOk.Text("Done !");
  bOk.SetPosition(238, 290);
  bOk.DefaultImage("go_button.png");
  bOk.OverImage("go_button_over.png");
  bOk.SetSize(164, 40);
  bOk.SetFont("BtnDone.ttf");

  pBarGlobal.SetActualValue(0);
  pBarGlobal.SetMaxValue(100);
  pBarGlobal.SetSize(270, 40);
  pBarGlobal.SetPosition(185, 190);
  pBarGlobal.SetText("Sciifii is analysing your choice!");
  pBarGlobal.SetFont("ProgressBar.ttf");
  
  pBarActual.SetActualValue(0);
  pBarActual.SetMaxValue(1);
  pBarActual.SetSize(270, 40);
  pBarActual.SetPosition(185, 240);
  pBarActual.SetFont("ProgressBar.ttf");
  
  mb.SetTitlePosition(16, 2);
  mb.SetTitleSize(279, 26);
  mb.SetTextPosition(16, 64);
  mb.SetTextSize(279, 45);
  mb.SetButtonPosition(76, 137);
  mb.DefaultButtonImage("go_button.png");
  mb.OverButtonImage("go_button_over.png");
  mb.SetMessageBoxImage("error_popup_screen.png");
  mb.SetFont("MessageBox.ttf");
  mb.UpDefaultImage("arrow_up.png");
  mb.UpOverImage("arrow_up_over.png");
  mb.UpClickedImage("arrow_up.png");
  mb.DownDefaultImage("arrow_down.png");
  mb.DownOverImage("arrow_down_over.png");
  mb.DownClickedImage("arrow_down.png");
  mb.ScrollBarImage("scrollbar.png");
  mb.ScrollBallImage("scrollball.png");
  

  AddChildren(&pBarActual);
  AddChildren(&pBarGlobal);
  AddChildren(&bOk);
  AddChildren(&bw);
	
  Control::InitializeComponents();
}

void GSciifiiLauncher2::Exit(Object *sender, CursorEventArgs *p)
{
  Visible(false);
}

static bool jobAlreadyDone = false;
static bool preparationPhase = true;
static u16 stepIndex = 0;

void GSciifiiLauncher2::LaunchProcess()
{
	if(jobAlreadyDone)
		return;

	if(preparationPhase && stepIndex == 0)
	{
		Config::ValidateOptions();
		UIManager::TrackWPads(false);
	}

	if(preparationPhase)
	{
		if(!Prepare())
		{
			bOk.Enabled(true);
			bOk.Visible(true);
			UIManager::TrackWPads(true);
			jobAlreadyDone = true;
			throw Exception("An error occured during prepare.");
		}
	}
	else
	{
		try
		{
			Execute();
		}
		catch(...)
		{
			jobAlreadyDone = true;
			UIManager::TrackWPads(true);
			mb.Show( "erreur dans process",  "Exception");
			return;
		}
	}

	if(jobAlreadyDone)
	{
		UIManager::TrackWPads(true);
		bOk.Text("Done !");
		bOk.Enabled(true);
		pBarActual.SetText("Done !");
		pBarActual.SetActualValue(100);
		pBarGlobal.SetText("Done !");
		pBarGlobal.SetActualValue(100);
	}
}

bool GSciifiiLauncher2::Prepare()
{
  //bool sucess = true;
  //pBarGlobal.SetText("Preparation");
  //u32 step = 0;
  vector<Installer*> steps = Config::Steps();
  //pBarGlobal.SetMaxValue(steps.size() * 2);
  bool success = steps[stepIndex++]->Prepare();

  if(stepIndex == steps.size())
  {
	  preparationPhase = false;
	  stepIndex = 0;
  }

  return success;
  /*for (vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
  {
    sucess &= (*ite)->Prepare();
    step++;
    pBarGlobal.SetActualValue(step);
    stringstream s;
    s << "Step " << step << " / " << steps.size() * 2;
    pBarGlobal.SetText(s.str());
  }
  return sucess;*/
}

void GSciifiiLauncher2::Execute()
{
	Installer* st = Config::Steps()[stepIndex++];

  try
  {
	st->Install();
  }
  catch (SystemException &ex)
  {
	bool ignore = false;
	for (vector<s32>::iterator itex = st-> IgnoredExceptions().begin(); itex != st->IgnoredExceptions().end(); itex++)
	  if (*itex == ex.GetCode())
	  {
		ignore = true;
		break;
	  }

	if (!ignore)
	  throw;
  }

  if(stepIndex == Config::Steps().size())
	{
	  jobAlreadyDone = true;
	  stepIndex = 0;
	}
}

void GSciifiiLauncher2::Draw()
{
  Menu_DrawRectangle(157, 160, 326, 190, Colors::White(), 1);
  Menu_DrawRectangle(158, 161, 324, 188, BackgroundColor(), 1);
  LaunchProcess();
  Control::Draw();
}

