#include <sciifii/ui/graphic/GSciifiiLauncher.h>
#include <Libwiisys/Exceptions/AbortException.h>
#include <sciifii/Sciifii.h>
#include <Libwiisys/Logging/Log.h>
#include <sciifii/ui/text/VirtualPad.h>
#include <Libwui/UIManager.hpp>
#include <libwui/Resources/Colors.h>
#include <Libwui/video.h>
#include <sstream>
#include <libwiisys/threading/ThreadResultEvent.h>
#include <libwiisys/threading/ThreadResultEventArgs.h>

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



GSciifiiLauncher::GSciifiiLauncher()
{}
void GSciifiiLauncher::InitializeComponents()
{

  Visible(true);
  BackgroundColor(Colors::FromRGBA(122, 122 ,122,125));
  SetPosition(0,0);
  SetSize(640, 480);

  bOk.Enabled(false);
  bOk.Visible(false);
  bOk.Click+=MakeDelegate(this,& GSciifiiLauncher::Exit);
  bOk.Text("Done !");
  bOk.SetPosition(220,250);
  bOk.DefaultImage("sd:/sciifii/default/go_button.png");
  bOk.OverImage("sd:/sciifii/default/go_button_over.png");
  bOk.SetSize(164, 40);


  pBarGlobal.SetActualValue(0);
  pBarGlobal.SetMaxValue(100);
  pBarGlobal.SetSize(200,20);
  pBarGlobal.SetPosition(220,190);


  pBarActual.SetActualValue(0);
  pBarActual.SetMaxValue(1);
  pBarActual.SetSize(200,20);
  pBarActual.SetPosition(220,220);


  AddChildren(&pBarActual);
  AddChildren(&pBarGlobal);
  AddChildren(&bOk);
  Control::InitializeComponents();
  Run();

}
bool GSciifiiLauncher::Run()
{
  try
  {
    bw.DoWork+=MakeDelegate(this,&GSciifiiLauncher::LaunchProcess);
    bw.WorkDone+=MakeDelegate(this,&GSciifiiLauncher::JobDone);
    bw.RunWorkerAsync(NULL);
  }
  catch(...)
  {
    return false;
  }
  return true;
}
GSciifiiLauncher::~GSciifiiLauncher()
{}

void GSciifiiLauncher::SetValueGlobal(Object *sender, ProgressEventArgs *p)
{
  pBarGlobal.SetValue(sender,p);
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
  Config::ValidateOptions();

  vector<Installer*> steps = Config::Steps();
  for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
    (*ite)->Progressing += MakeDelegate(this, &GSciifiiLauncher::SetValueActual);
  UIManager::TrackWPads(false);
  if (Prepare())
  {
    Execute();
    pBarGlobal.SetText("Done !");
  }
  else
  {
    bOk.Enabled(true);
    bOk.Visible(true);
    UIManager::TrackWPads(true);
    throw Exception("An error occured during prepare.");
  }

  UIManager::TrackWPads(true);
}


bool GSciifiiLauncher::Prepare()
{
  bool sucess = true;
  pBarGlobal.SetText("Preparation");
  u32 step=0;
  vector<Installer*> steps = Config::Steps();
  pBarGlobal.SetMaxValue(steps.size()*2);
  for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
  {
    sucess &= (*ite)->Prepare();
    step++;
    pBarGlobal.SetActualValue(step);
    stringstream s;
    s<<"Step "<<step<<" / "<<steps.size()*2;
    pBarGlobal.SetText(s.str());
  }
  return sucess;
}

void GSciifiiLauncher::Execute()
{
  pBarGlobal.SetText("Installation");
  vector<Installer*> steps = Config::Steps();
  u32 step=steps.size();
  for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
  {
    try
    {
      pBarGlobal.SetActualValue(step+steps.size());
      stringstream s;
      s<<"Step "<<step<<" / "<<steps.size()*2;
      pBarGlobal.SetText(s.str());
      step++;
      (*ite)->Install();
    }
    catch(SystemException &ex)
    {
      bool ignore = false;
      for(vector<s32>::iterator itex = (*ite)->
                                       IgnoredExceptions().begin();
          itex != (*ite)->IgnoredExceptions().end();
          itex++)
        if(*itex == ex.GetCode()
          )
        {
          ignore = true;
          break;
        }

      if(!ignore)
        throw;
      else
      {
        pBarActual.SetActualValue(100);
        pBarActual.SetText("Step skipped !");
      }
    }



    (*ite)->Progressing -= MakeDelegate(this, &GSciifiiLauncher::SetValueActual);
    delete *ite;
  }
}

void GSciifiiLauncher::JobDone(Object* sender, ThreadResultEventArgs* args)
{
  if( args->Result.HasError)
  {
    bOk.Text("Error !");
  }
  else
  {
    bOk.Text("Done !");
  }

  pBarActual.SetText("Done !");
  pBarActual.SetActualValue(100);
  pBarGlobal.SetText("Done !");
  pBarGlobal.SetActualValue(100);

  bOk.Visible(true);
  bOk.Enabled(true);
}
void GSciifiiLauncher::Draw()
{
  Menu_DrawRectangle(190,160,256,160, Colors::White(), 1);
  Menu_DrawRectangle(191,161,254,158, BackgroundColor(), 1);
  Control::Draw();
}

