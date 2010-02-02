#include "TruchaRestorer.h"

#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/system/TitlePatcher.h>
#include <libutils/system/SimplePatch.h>
#include "../Config.h"
#include <iostream>

using namespace fastdelegate;
using namespace std;

TruchaRestorer::TruchaRestorer(u32 titleId, u16 revision, const string& wadFolder)
: Installer(wadFolder),
  _id(0x0000000100000000ULL + titleId),
  _revision(revision)
{}

bool TruchaRestorer::Prepare()
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

	OnProgress("Trucha restorer preparation done.", 1);
	return true;
}

void TruchaRestorer::Install()
{
	struct mallinfo mi1, mi2;
	
	u32 shortId = (u32)_id;
	
	stringstream wad;
	wad << wadFolder << "/IOS" << shortId << "v" << _revision << ".wad";

	MINIT;
	TitlePatcher newTitle;	
	M2("Creation of the patcher");
	M1;
	newTitle.AddPatch(SimplePatch::ES_HashCheck_Old());
	M2("Add ES hash check 1 patch");
	M1;
	newTitle.AddPatch(SimplePatch::ES_HashCheck_New());
	M2("Add ES hash check 2 patch");
	M1;
	newTitle.AddPatch(SimplePatch::ES_Identify());
	M2("Add ES identify patch");
	M1;
	newTitle.AddPatch(SimplePatch::FFS_PermsCheck());
	M2("Add FFS permscheck patch");

	OnProgress("Loading title from IOS and aply patches", 0.25);
	
	M1;
    newTitle.LoadFromWad(wad.str() , "sd:/temp");
	M2("Loading from wad");
	
    stringstream inst;
    inst << "Installing title.";
	
	M1;
    OnProgress(inst.str(), 0.75);
	M2("Declaring progression");
	M1;
	newTitle.Install();
	M2("Installation");
	
	OnProgress("Trucha bug restored.", 1);
}
