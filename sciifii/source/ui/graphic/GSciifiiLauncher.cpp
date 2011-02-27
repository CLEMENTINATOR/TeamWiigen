#include <sciifii/ui/graphic/GSciifiiLauncher.h>
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

void GSciifiiLauncher::InitializeComponents()
{
  BackgroundColor(Colors::FromRGBA(122, 122, 122, 125));
  SetPosition(0, 0);
  SetSize(640, 480);

  bOk.Enabled(false);
  bOk.Click += MakeDelegate(this, &GSciifiiLauncher::Exit);
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
  Run();
}

bool GSciifiiLauncher::Run()
{
  try
  {
    UIManager::TrackWPads(false);
	Config::ValidateOptions();

    vector<Installer*> steps = Config::Steps();
    for (vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
      (*ite)->Progressing += MakeDelegate(this,&GSciifiiLauncher::SetValueActual);
	  
    bw.DoWork += MakeDelegate(this, &GSciifiiLauncher::LaunchProcess);
    bw.WorkDone += MakeDelegate(this, &GSciifiiLauncher::JobDone);
    bw.RunWorkerAsync(NULL);
  }
  catch (...)
  {
    return false;
  }
  return true;
}

void GSciifiiLauncher::SetValueGlobal(Object *sender, ProgressEventArgs *p)
{
  pBarGlobal.SetValue(sender, p);
}

void GSciifiiLauncher::SetValueActual(Object *sender, ProgressEventArgs *p)
{
  pBarActual.SetValue(sender, p);
}

void GSciifiiLauncher::Exit(Object *sender, CursorEventArgs *p)
{
  Visible(false);
}

void GSciifiiLauncher::LaunchProcess(Object *sender, Object *args)
{
  if (Prepare())
  {
    Execute();
    //pBarGlobal.SetText("Done !");
  }
  else
    throw Exception("An error occured during prepare.");
}

bool GSciifiiLauncher::Prepare()
{
  bool sucess = true;
  //pBarGlobal.SetText("Preparation");
  u32 step = 0;
  vector<Installer*> steps = Config::Steps();
  //pBarGlobal.SetMaxValue(steps.size() * 2);
  for (vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
  {
    sucess &= (*ite)->Prepare();
    step++;
    //pBarGlobal.SetActualValue(step);
    stringstream s;
    s << "Step " << step << " / " << steps.size() * 2;
    //pBarGlobal.SetText(s.str());
  }
  return sucess;
}

void GSciifiiLauncher::Execute()
{
  //pBarGlobal.SetText("Installation");
  vector<Installer*> steps = Config::Steps();
  u32 step = 0;
  for (vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
  {
    try
    {
      //pBarGlobal.SetActualValue(step + steps.size());
      stringstream s;
      s << "Step " << step + steps.size() << " / " << steps.size() * 2;
      //pBarGlobal.SetText(s.str());
      step++;
      (*ite)->Install();
    }
    catch (SystemException &ex)
    {
      bool ignore = false;
      for (vector<s32>::iterator itex = (*ite)-> IgnoredExceptions().begin(); itex != (*ite)->IgnoredExceptions().end(); itex++)
        if (*itex == ex.GetCode())
        {
          ignore = true;
          break;
        }

      if (!ignore)
        throw;
      else
      {
        //pBarActual.SetActualValue(1);
        //pBarActual.SetText("Step skipped !");
      }
    }
  }
}

void GSciifiiLauncher::JobDone(Object* sender, ThreadResultEventArgs* args)
{
  vector<Installer*> steps = Config::Steps();
  for (vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
    (*ite)->Progressing -= MakeDelegate(this,&GSciifiiLauncher::SetValueActual);
  UIManager::TrackWPads(true);
  
  if (args->Result.HasError)
    mb.Show( args->Result.e->ToString(),  "Exception");
  else
  {
    bOk.Text("Done !");
    pBarActual.SetText("Done !");
    pBarActual.SetActualValue(100);
    pBarGlobal.SetText("Done !");
    pBarGlobal.SetActualValue(100);
  }

  bOk.Enabled(true);
}

void GSciifiiLauncher::Draw()
{
  Menu_DrawRectangle(157, 160, 326, 190, Colors::White(), 1);
  Menu_DrawRectangle(158, 161, 324, 188, BackgroundColor(), 1);
  Control::Draw();
}

