#include "TruchaRestorer.h"

#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/system/TitlePatcher.h>
#include <libutils/system/SimplePatch.h>
#include "../Config.h"
#include <iostream>

using namespace fastdelegate;
using namespace std;

TruchaRestorer::TruchaRestorer(u32 titleId, u16 revision)
: _id(0x0000000100000000ULL + titleId),
  _revision(revision)
{}

bool TruchaRestorer::Prepare()
{
	u32 shortId = (u32)_id;

	stringstream wad;
	wad << Config::WorkingDirectory() << "/IOS" << shortId << "v" << _revision << ".wad";

	if(!File::Exists(wad.str()))
	{
		if(Config::HasNetwork())
		{
			Title ios;

			stringstream down;
			down << "Loading IOS" << shortId << "v" << _revision << " from NUS.";
			OnProgress(down.str(), 0.25);
			ios.LoadFromNusServer(_id, 0, Config::WorkingDirectory());

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
	u32 shortId = (u32)_id;

	stringstream wad;
	wad << Config::WorkingDirectory() << "/IOS" << shortId << "v" << _revision << ".wad";

	TitlePatcher newTitle(_id, 0xFFFF);
	newTitle.AddPatch(SimplePatch::ES_HashCheck_Old());
	newTitle.AddPatch(SimplePatch::ES_HashCheck_New());
	newTitle.AddPatch(SimplePatch::ES_Identify());
	newTitle.AddPatch(SimplePatch::FFS_PermsCheck());

	OnProgress("Loading title from IOS and applying patches", 0.25);

    newTitle.LoadFromWad(wad.str() , "sd:/temp");

    stringstream inst;
    inst << "Installing title.";

    OnProgress(inst.str(), 0.75);
	newTitle.Install();

	OnProgress("Trucha bug restored.", 1);
}
