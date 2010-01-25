#include <iostream>
#include <fastdelegate.h>

#include <libutils/fs/Device.h>
#include <libutils/system/Identification.h>

#include "Sciifii.h"

#include <libutils/fs/Directory.h>

#include "business/Cios.h"
#include "business/CiosCorp.h"
#include "business/IosDowngrader.h"
#include "business/TitleInstaller.h"
#include "business/TruchaRestorer.h"
#include "business/IosReloader.h"

using namespace fastdelegate;
using namespace std;

Sciifii::Sciifii()
{
	string dir = "sd:/sciifii";
	
	steps.push_back(new IosDowngrader(0x000000010000000fULL, 257, dir));
	steps.push_back(new IosReloader(15, UserType_SU, "sd:/"));
	steps.push_back(new TruchaRestorer(0x00000001000000024ULL, 0, dir));
	steps.push_back(new IosReloader(36, UserType_SU, "sd:/"));
	steps.push_back(new TitleInstaller(0x0000000100000000fULL, 0, dir));
	steps.push_back(new Cios(dir));
	steps.push_back(new IosReloader(249, UserType_SU, "sd:/"));
	steps.push_back(new CiosCorp(dir));
	
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
	cout << (u8)args->percent << "%: " << args->message << endl;
}

bool Sciifii::Prepare()
{
	bool error = false;

	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		error |= (*ite)->Prepare();

	return error;
}

void Sciifii::Execute()
{
	Identification::IdentifyAs(UserType_SU);

	for(vector<Installer*>::iterator ite = steps.begin(); ite != steps.end(); ite++)
		(*ite)->Install();
}
