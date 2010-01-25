#include "TitleInstaller.h"

#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>
using namespace fastdelegate;
using namespace std;

TitleInstaller::TitleInstaller(u64 titleId, u16 revision, const std::string& wadFolder)
: Installer(wadFolder),
  _id(titleId),
  _revision(revision)
{}

bool TitleInstaller::Prepare()
{
	u32 shortId = (u32)_id;
	
	stringstream wad;
	wad << wadFolder << "/IOS" << shortId << "v" << _revision << ".wad";
	
	if(!File::Exists(wad.str()))
	{
		if(Config::HasNetwork())
		{
			Title ios;

			stringstream down;
			down << "Loading IOS" << shortId << "v" << _revision << " from NUS.";
			OnProgress(down.str(), 0.25);
			ios.LoadFromNusServer(_id, 0, wadFolder);

			stringstream pack;
			pack << "Saving as IOS" << shortId << "v" << _revision << ".wad.";
			OnProgress(pack.str(), 0.75);
			ios.PackAsWad(wad.str());
		}
		else
		{
			cout << "You arent connected to the network and some wads are missing." << endl
				 << "Please refer to the readme.";
			return false;
		}
	}

	OnProgress("Title installation preparation done.", 1);
	return true;
}

void TitleInstaller::Install()
{
	u32 shortId = (u32)_id;
	
	stringstream wad;
	wad << wadFolder << "/IOS" << shortId << "v" << _revision << ".wad";

	Title newTitle;	

	stringstream load;
	load << "Loading title from IOS" << shortId << "v" << _revision << ".wad";
	OnProgress(load.str(), 0.25);
    newTitle.LoadFromWad(wad.str() , "sd:/temp");

    stringstream inst;
    inst << "Installing title.";
    OnProgress(inst.str(), 0.75);
	newTitle.Install();

	OnProgress("Title installation done.", 1);
}
