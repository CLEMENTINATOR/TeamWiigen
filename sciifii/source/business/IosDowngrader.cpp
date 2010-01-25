#include "IosDowngrader.h"

#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>
using namespace fastdelegate;
using namespace std;

IosDowngrader::IosDowngrader(u64 titleId, u16 neededRevision, const std::string& wadFolder)
: Installer(wadFolder),
  _id(titleId),
  _neededRevision(neededRevision)
{}

bool IosDowngrader::Prepare()
{
	u32 shortId = (u32)_id;
	
	stringstream newWad;
	newWad << wadFolder << "/IOS" << shortId << ".wad";

	stringstream oldWad;
	oldWad << wadFolder << "/IOS" << shortId << "v" << _neededRevision << ".wad";
	
	if((!File::Exists(newWad.str()) || !File::Exists(oldWad.str())) && !hasNetwork)
	{
		cout << "You arent connected to the network and some wads are missing." << endl
			 << "Please refer to the readme.";
		return false;
	}
	
	if(!File::Exists(newWad.str()))
	{
		Title ios;
		ios.LoadFromNusServer(_id, 0, wadFolder);
		ios.PackAsWad(newWad.str());
	}
	
	if(!File::Exists(oldWad.str()))
	{
		Title ios;
		ios.LoadFromNusServer(_id, _neededRevision, wadFolder);
		ios.PackAsWad(oldWad.str());
	}

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
		
	//this will be aborted by the event handler
	newTitle.Install();

	//this will install the needed revision
	oldTitle.Install();
}

void IosDowngrader::DowngradeTmd(Object* sender, TitleEventArgs *args)
{
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
	args->skipStep = true;
}
