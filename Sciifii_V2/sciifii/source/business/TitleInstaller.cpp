#include "TitleInstaller.h"
#include <iomanip>
#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>
using namespace fastdelegate;
using namespace std;

TitleInstaller::TitleInstaller(u64 titleId, u16 revision)
: _id(titleId),
  _revision(revision)
{}

bool TitleInstaller::Prepare()
{
	stringstream wad;
	wad << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);
	
	if(!File::Exists(wad.str()))
	{
		if(Config::HasNetwork())
		{
			Title ios;

			stringstream down;
			down << "Downloading title " << hex << setfill('0') << setw(16) << _id << dec;
			if( _revision!=0) down<< " version " << _revision ;
			down << " from NUS.";
			OnProgress(down.str(), 0.25);
			ios.LoadFromNusServer(_id, 0, Config::WorkingDirectory());

			stringstream pack;
			pack << "Saving as " << Path::GetFileName(wad.str());
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
	stringstream wad;
	wad << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);

	Title newTitle;

	stringstream load;
	load << "Loading title " << hex << setfill('0') << setw(16) << _id << dec;
	if(_revision!=0) 
		load << "v" << _revision;
	load << " from Wad.";
	
	OnProgress(load.str(), 0.25);
    newTitle.LoadFromWad(wad.str() , "sd:/temp");

    stringstream inst;
    inst << "Installing title.";
    OnProgress(inst.str(), 0.75);
	newTitle.Install();

	OnProgress("Title installation done.", 1);
}
