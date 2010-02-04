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

using namespace fastdelegate;
using namespace std;

#define TITLE_IOS(x) (0x0000000100000000ULL + x)

Sciifii::Sciifii()
: hasDisplayed(false)
{
	string dir = "sd:/sciifii";
	
	if(Config::RestoreTrucha())
	{
		//Downgrade IOS
		steps.push_back(new IosDowngrader(Config::DowngradeIos(), Config::DowngradeIosRevision(), dir));
		steps.push_back(new IosReloader(Config::DowngradeIos(), UserType_SU, "sd:/"));
		
		//Restore Trucha bug
		steps.push_back(new TruchaRestorer(Config::TruchaIOS(), 0, dir));
	}
	
	if(Config::RestoreTrucha() || Config::InstallCios())
		steps.push_back(new IosReloader(Config::TruchaIOS(), UserType_SU, "sd:/"));
	
	//Repair downgraded ios
	if(Config::RestoreTrucha())
		steps.push_back(new TitleInstaller(TITLE_IOS(Config::DowngradeIos()), 0, dir));
		
	//install cios
	if(Config::InstallCios())
		steps.push_back(new Cios(dir));
	
	steps.push_back(new IosReloader(249, UserType_SU, "sd:/"));
	
	//Repair tbr ios
	if(Config::RestoreTrucha())
		steps.push_back(new TitleInstaller(TITLE_IOS(Config::TruchaIOS()), 0, dir));
	
	if(Config::InstallCorp())
		steps.push_back(new CiosCorp(dir));
		
	if(Config::UpdateSystem() && Config::InstallCorp())
		steps.push_back(new SystemUpdater(Config::PartialUpdateList(), dir));
	else if(Config::UpdateSystem() )
		steps.push_back(new SystemUpdater(Config::UpdateList(), dir));
	
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Progressing += MakeDelegate(this, &Sciifii::DisplayProgress);
}

Sciifii::~Sciifii()
{
	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		delete *ite;
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
