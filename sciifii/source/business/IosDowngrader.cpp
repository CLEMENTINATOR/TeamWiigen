#include "IosDowngrader.h"

#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>
using namespace fastdelegate;
using namespace std;

IosDowngrader::IosDowngrader(u32 titleId, u16 neededRevision, const std::string& wadFolder)
: Installer(wadFolder),
  _id(0x0000000100000000ULL + titleId),
  _neededRevision(neededRevision)
{}

bool IosDowngrader::Prepare()
{
	u32 shortId = (u32)_id;
	
	stringstream newWad;
	newWad << wadFolder << "/IOS" << shortId << ".wad";

	stringstream oldWad;
	oldWad << wadFolder << "/IOS" << shortId << "v" << _neededRevision << ".wad";
	
	if((!File::Exists(newWad.str()) || !File::Exists(oldWad.str())) && !Config::HasNetwork())
	{
		cout << "You arent connected to the network and some wads are missing." << endl
			 << "Please refer to the readme.";
		return false;
	}
	
	if(!File::Exists(newWad.str()))
	{
		Title ios;

		stringstream downloadMessage;
		downloadMessage << "Downloading IOS" << shortId << " from NUS.";
		OnProgress(downloadMessage.str(), 0);
		ios.LoadFromNusServer(_id, 0, wadFolder);

		stringstream packMessage;
		packMessage << "Save as IOS" << shortId << ".wad.";
		OnProgress(packMessage.str(), 0.25);
		ios.PackAsWad(newWad.str());
	}
	
	if(!File::Exists(oldWad.str()))
	{
		Title ios;

		stringstream downloadMessage;
		downloadMessage << "Downloading IOS" << shortId << "v" << _neededRevision << " from NUS.";
		OnProgress(downloadMessage.str(), 0.5);
		ios.LoadFromNusServer(_id, _neededRevision, wadFolder);

		stringstream packMessage;
		packMessage << "Save as IOS" << shortId << "v" << _neededRevision << ".wad.";
		OnProgress(packMessage.str(), 0.75);
		ios.PackAsWad(oldWad.str());
	}

	OnProgress("Downgrade preparation done.", 1);
	return true;
}

void IosDowngrader::Install()
{
	u32 shortId = (u32)_id;
	
	stringstream oldFile;
	oldFile << wadFolder << "/IOS" << shortId << "v" << _neededRevision << ".wad";

	stringstream newFile;
	newFile<< wadFolder << "/IOS" << shortId << ".wad";
	
	Title newTitle;	
	newTitle.TmdInstalledEvent += MakeDelegate(this, &IosDowngrader::DowngradeTmd);
    newTitle.LoadFromWad(newFile.str() , "sd:/temp");
	
	Title oldTitle;
	oldTitle.TicketInstallingEvent += MakeDelegate(this, &IosDowngrader::SkipStep);
	oldTitle.LoadFromWad(oldFile.str(), "sd:/temp");
		
	OnProgress("Installing the fake IOS", 0.2);
	//this will be aborted by the event handler
	newTitle.Install();

	OnProgress("Installing the good IOS.",0.6);
	//this will install the needed revision
	oldTitle.Install();

	OnProgress("IOS downgraded.", 1);
}

void IosDowngrader::DowngradeTmd(Object* sender, TitleEventArgs *args)
{
	OnProgress("Downgrading tmd.", 0.4);
	string tmd_path = "wii:/tmp/title.tmd";
	File::Delete(tmd_path);

	u8 *ptmd = (u8*) (args->buffer.Content());

	ptmd[0x1dc] = 0; //set revision to 0
	ptmd[0x1dd] = 0; // set the content number to 0

	File &f_tmd = File::Create(tmd_path);
	f_tmd.Write(args->buffer);
	f_tmd.Close();
	delete &f_tmd;

	ES_AddTitleFinish();

	args->abortProcess = true;
}

void IosDowngrader::SkipStep(Object* sender, TitleEventArgs *args)
{
	OnProgress("Skipping ticket installation.", 0.8);
	args->skipStep = true;
}
