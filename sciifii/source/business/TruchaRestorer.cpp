#include "TruchaRestorer.h"

#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
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
	wad << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);

	if(!File::Exists(wad.str()))
	{
		if(Config::HasNetwork())
		{
			Title ios;
			stringstream down;
			down << "Loading IOS" << shortId;
			if(_revision!=0) down << "v" << _revision;
			down  << " from NUS.";
			OnProgress(down.str(), 0.25);
			ios.LoadFromNusServer(_id, 0, Config::WorkingDirectory());

			stringstream pack;
			pack << "Saving as " << Path::GetFileName(wad.str());

			OnProgress(pack.str(), 0.75);
			ios.PackAsWad(wad.str());
		}
		else
		{
			cout << "Network unavailable and wad files missing. Please refer to the readme." << endl;
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
	wad << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);

	TitlePatcher newTitle(_id, 0xFFFF);
	newTitle.AddPatch(SimplePatch::ES_HashCheck_Old());
	newTitle.AddPatch(SimplePatch::ES_HashCheck_New());
	newTitle.AddPatch(SimplePatch::ES_Identify());
	newTitle.AddPatch(SimplePatch::FFS_PermsCheck());

	stringstream install;
	install << "Loading IOS" <<shortId;
	if(_revision!=0)
		install << "v" << _revision;
    install<<" from Wad and applying patches";
	OnProgress(install.str(), 0.25);

    newTitle.LoadFromWad(wad.str() , "sd:/temp");

    stringstream inst;
    inst << "Installing title.";

    OnProgress(inst.str(), 0.75);
	newTitle.Install();

	OnProgress("Trucha bug restored.", 1);
}
