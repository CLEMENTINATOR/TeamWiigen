#include <iostream>
#include <sstream>
#include <fastdelegate.h>

#include <libutils/fs/Device.h>
#include <libutils/system/Identification.h>

#include "Sciifii.h"
#include "Config.h"

#include <libutils/fs/Directory.h>
#include <libutils/logging/GeckoLogger.h>
#include <libutils/logging/FileLogger.h>

#include <libutils/logging/Log.h>
using namespace fastdelegate;
using namespace std;

#define TITLE_IOS(x) (0x0000000100000000ULL + x)

Sciifii::Sciifii()
: hasDisplayed(false)
{
	vector<Installer*> steps = Config::Steps();
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Progressing += MakeDelegate(this, &Sciifii::DisplayProgress);
}

Sciifii::~Sciifii()
{
	vector<Installer*> steps = Config::Steps();
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Progressing -= MakeDelegate(this, &Sciifii::DisplayProgress);
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
	if(args->percent==1)	Log::WriteLog(Log_Info,message.str());

	cout << message.str() << flush;
	Sciifii::LastStepMessage() = message.str();

	hasDisplayed = true;

	VIDEO_WaitVSync();
}

bool Sciifii::Prepare()
{
	bool sucess = true;

	cout << "Sciifii is preparing required elements." << endl;
	 Log::WriteLog(Log_Info,"Sciifii is preparing required elements.");
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
	 Log::WriteLog(Log_Info,"Please wait until sciifii finish the installation.");
	vector<Installer*> steps = Config::Steps();
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
	{
		(*ite)->Install();
		if(hasDisplayed)
		{
			cout << endl;
			hasDisplayed = false;
		}
	}
}

string& Sciifii::LastStepMessage()
{
	static string _lastStepMessage = "";
	return _lastStepMessage;
}
