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
}

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

void GSciifiiLauncher::LaunchProcess()
{
	static u16 stepIndex = 0;
	static bool prepare = true;
	static bool endJob = false;
	
	if(endJob)
		return;
		
	//initialisation of ui
	if(stepIndex == 0 && prepare)
	{
		UIManager::TrackWPads(false);
		Config::ValidateOptions();
	}
	else if(stepIndex == 0)
	{
		pBarGlobal.SetText("Installation");
	}
	
	//getting all the steps
  vector<Installer*> steps = Config::Steps();
	
	//initialisation of execution
	if(stepIndex == 0 && prepare)
	{		
		pBarGlobal.SetMaxValue(steps.size()*2);
		pBarGlobal.SetText("Preparation");
		
		//attach the handlers
		for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
			(*ite)->Progressing += MakeDelegate(this, &GSciifiiLauncher::SetValueActual);  
	}
	
	//doing the stuff
	if(prepare)
	{
		endJob = !(steps[stepIndex]->Prepare());
		pBarGlobal.SetActualValue(stepIndex);
		stringstream s;
		s<< "Step " << stepIndex << " / " << steps.size() * 2;
		pBarGlobal.SetText(s.str());
		stepIndex++;
		if(stepIndex == steps.size())
		{
			prepare = !prepare;
			stepIndex = 0;
		}
	}
	else
	{
		try
		{
				pBarGlobal.SetActualValue(stepIndex + steps.size());
				stringstream s;
				s << "Step " << stepIndex << " / " << steps.size() * 2;
				pBarGlobal.SetText(s.str());
				steps[stepIndex]->Install();
				stepIndex++;
		}
		catch(SystemException &ex)
		{
			bool ignore = false;
			for(vector<s32>::iterator itex = steps[stepIndex]->IgnoredExceptions().begin(); itex != steps[stepIndex]->IgnoredExceptions().end(); itex++)
				if(*itex == ex.GetCode())
				{
					ignore = true;
					break;
				}

			if(!ignore)
				endJob = true;
			else
			{
				pBarActual.SetActualValue(100);
				pBarActual.SetText("Step skipped !");
			}
		}
		catch(...)
		{
			endJob = true;
		}

		steps[stepIndex]->Progressing -= MakeDelegate(this, &GSciifiiLauncher::SetValueActual);
		
		if(stepIndex == steps.size())
			endJob = true;
	}
	
  if(endJob)
	{
		bOk.Enabled(true);
    bOk.Visible(true);
    UIManager::TrackWPads(true);
	}
}

void GSciifiiLauncher::Draw()
{
	LaunchProcess();
  Menu_DrawRectangle(190,160,256,160, Colors::White(), 1);
  Menu_DrawRectangle(191,161,254,158, BackgroundColor(), 1);
  Form::Draw();
}

