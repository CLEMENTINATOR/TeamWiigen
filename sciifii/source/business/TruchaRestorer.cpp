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
			ios.LoadFromNusServer(_id, 0, wadFolder);
			ios.PackAsWad(wad.str());
		}
		else
		{
			cout << "You arent connected to the network and some wads are missing." << endl
				 << "Please refer to the readme.";
			return false;
		}
	}

	return true;
}

void TruchaRestorer::Install()
{
	u32 shortId = (u32)_id;
	
	stringstream wad;
	wad << wadFolder << "/IOS" << shortId << "v" << _revision << ".wad";

	TitlePatcher newTitle;	
	newTitle.AddPatch(SimplePatch::ES_HashCheck_Old());
	newTitle.AddPatch(SimplePatch::ES_HashCheck_New());
	newTitle.AddPatch(SimplePatch::ES_Identify());

	
    newTitle.LoadFromWad(wad.str() , "sd:/temp");
	newTitle.Install();
}
