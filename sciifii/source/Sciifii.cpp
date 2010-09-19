#include <iostream>
#include <sstream>
#include <fastdelegate.h>

#include <libwiisys.h>
#include "Sciifii.h"
#include "Config.h"



using namespace fastdelegate;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;


#define TITLE_IOS(x) (0x0000000100000000ULL + x)

Sciifii::Sciifii()
: hasDisplayed(false)
{
	vector<Installer*> steps = Config::Steps();
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Progressing += MakeDelegate(this, &Sciifii::DisplayProgress);
}

void Sciifii::DisplayProgress(Object* sender, ProgressEventArgs* args)
{
	//erase the line
	s32 cols, rows;
	CON_GetMetrics(&cols, &rows);
	cout << "\r";
	for(rows = 1; rows < cols; rows++)
		cout << " ";
	cout << "\r";

	// send the message
	stringstream message;
	message << (u32)(args->percent * 100) << "%:\t" << args->message;
	cout << message.str() << flush;
	if(args->percent==1)	Log::WriteLog(Log_Info,message.str());

	Sciifii::LastStepMessage() = message.str();

	hasDisplayed = true;

	VIDEO_WaitVSync();
}

bool Sciifii::Prepare()
{
	bool sucess = true;

	cout << "Sciifii is preparing required elements." << endl;

	vector<Installer*> steps = Config::Steps();
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
	{
		sucess &= (*ite)->Prepare();
		if(hasDisplayed)
		{
			cout << endl;
			hasDisplayed = false;
		}
	}

	return sucess;
}

void Sciifii::Execute()
{
	cout << "Please wait until sciifii finish the installation." << endl;

	vector<Installer*> steps = Config::Steps();
	MEM_DEBUG_INIT
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
	{
		try
		{
		  (*ite)->Install();
		  MEM_DEBUG_FOLLOW("Step")
		}
		catch(Exception& ex)
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
		  {
			cout << endl << "\x1b[33mStep skipped!\x1b[37m";
			hasDisplayed = true;
		  }
		}
    
		if(hasDisplayed)
		{
			cout << endl;
			hasDisplayed = false;
		}

		(*ite)->Progressing -= MakeDelegate(this, &Sciifii::DisplayProgress);
		delete *ite;
	}
}

string& Sciifii::LastStepMessage()
{
	static string _lastStepMessage = "";
	return _lastStepMessage;
}
