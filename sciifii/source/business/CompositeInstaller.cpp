#include "CompositeInstaller.h"

#include <fastdelegate.h>

using namespace std;
using namespace fastdelegate;

CompositeInstaller::CompositeInstaller(const string& name)
:  Installer(),
   _name(name)
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
		(*ite)->Install();
		(*ite)->Progressing -= MakeDelegate(this, &CompositeInstaller::DisplayProgress);
		_currentStep++;
	}
	
	OnProgress(_name + " installation done!", 1);
}