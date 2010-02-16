#include <iostream>
#include <fastdelegate.h>

#include <libutils/fs/Device.h>
#include <libutils/system/Identification.h>

#include "Sciifii.h"
#include "Config.h"

#include <libutils/fs/Directory.h>

#include "business/Cios.h"
#include "business/CiosCorp.h"
#include "business/IosDowngrader.h"
#include "business/TitleInstaller.h"
#include "business/TruchaRestorer.h"
#include "business/IosReloader.h"
#include "business/SystemUpdater.h"
#include "business/LoaderGX.h"

using namespace fastdelegate;
using namespace std;

#define TITLE_IOS(x) (0x0000000100000000ULL + x)

Sciifii::Sciifii()
: hasDisplayed(false)
{
	for(vector<Installer*>::iterator ite = Config::Steps().begin(); ite != Config::Steps().end(); ite++)
		steps.push_back(*ite);
		
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Progressing += MakeDelegate(this, &Sciifii::DisplayProgress);
}

Sciifii::~Sciifii()
{
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Progressing -= MakeDelegate(this, &Sciifii::DisplayProgress);
}

void Sciifii::DisplayProgress(Object* sender, ProgressEventArgs* args)
{
	//return to the begin of the line
	cout << "\r";

	//erase the line
	s32 cols, rows;
	CON_GetMetrics(&cols, &rows);
	for(rows = 1; rows < cols; rows++)
		cout << " ";

	cout << "\r";

	cout << (u32)(args->percent * 100) << "%:\t" << args->message;

	cout << flush;

	hasDisplayed = true;
	
	VIDEO_WaitVSync();
}

bool Sciifii::Prepare()
{
	bool error = false;

	cout << "Sciifii is preparing required elements." << endl;

	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
	{
		error |= (*ite)->Prepare();
		if(hasDisplayed)
		{
			cout << endl;
			hasDisplayed = false;
		}
	}

	return error;
}

void Sciifii::Execute()
{
	cout << "Please wait until sciifii finish the installation." << endl;
	
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
