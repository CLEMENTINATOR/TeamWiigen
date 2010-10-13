#include <FastDelegate.h>
#include <Sciifii.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;

CompositeInstaller::CompositeInstaller(const string& name)
:  Installer(),
   _name(name),
   _cleaned(false)
{}

void CompositeInstaller::DisplayProgress(Object* sender, ProgressEventArgs* args)
{
	f32 percent = (args->percent + _currentStep) / _steps.size();
	OnProgress(args->message, percent);
}

void CompositeInstaller::AddStep(Installer* step)
{
	_steps.push_back(step);
}

bool CompositeInstaller::Prepare()
{
	_currentStep = 0;
	for(vector<Installer*>::iterator ite = _steps.begin(); ite != _steps.end(); ite++)
	{
		(*ite)->Progressing += MakeDelegate(this, &CompositeInstaller::DisplayProgress);
		(*ite)->Prepare();
		(*ite)->Progressing -= MakeDelegate(this, &CompositeInstaller::DisplayProgress);
		_currentStep++;
	}
	
	OnProgress(_name + " preparation done!", 1);
	return true;
}

void CompositeInstaller::Install()
{
	_currentStep = 0;	
	for(vector<Installer*>::iterator ite = _steps.begin(); ite != _steps.end(); ite++)
	{
		(*ite)->Progressing += MakeDelegate(this, &CompositeInstaller::DisplayProgress);
		try
		{
			(*ite)->Install();
		}
		catch(SystemException& ex)
		{
		  bool ignore = false;
		  for(vector<s32>::iterator itex = (*ite)->IgnoredExceptions().begin(); itex != (*ite)->IgnoredExceptions().end(); itex++)
			if(*itex == ex.GetCode())
			{
			  ignore = true;
			  break;
			}

		  if(!ignore)
			throw;
		  else
			OnProgress("\x1b[33mSubstep skipped!\x1b[37m", (1 + _currentStep) / _steps.size());
		}
		(*ite)->Progressing -= MakeDelegate(this, &CompositeInstaller::DisplayProgress);
		delete *ite;
		_currentStep++;
	}
	
	_cleaned = true;
	OnProgress(_name + " installation done!", 1);
}
void CompositeInstaller::SendToLog()
{
	Log::WriteLog(Log_Info,"CompositeInstaller("+_name+")");
	for(vector<Installer*>::iterator ite = _steps.begin(); ite != _steps.end(); ite++)
	{
		(*ite)->SendToLog();
	}
	Log::WriteLog(Log_Info,"End of CompositeInstaller("+_name+")");
}

CompositeInstaller::~CompositeInstaller()
{
	if(!_cleaned)
		for(vector<Installer*>::iterator ite = _steps.begin(); ite != _steps.end(); ite++)
			delete *ite;
}
