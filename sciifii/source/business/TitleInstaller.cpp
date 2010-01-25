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

void TitleInstaller::Install()
{
	u32 shortId = (u32)_id;
	
	stringstream wad;
	wad << wadFolder << "/IOS" << shortId << "v" << _revision << ".wad";

	Title newTitle;	
    newTitle.LoadFromWad(wad.str() , "sd:/temp");
	newTitle.Install();
}
