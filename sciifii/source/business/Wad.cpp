#include "Wad.h"

#include <libutils/exception/Exception.h>
#include <libutils/system/Title.h>

#include "common/FileManager.h"

using namespace std;

Wad::Wad(const string &file, WadAction action)
: Installer(),
  _file(file),
  _action(action)
{}

bool Wad::Prepare()
{
	if(!FileManager::Download(_file))
		throw Exception("Error downloading " + _file, -1);
		
	return true;
}

void Wad::Install()
{
	Title t;
	t.LoadFromWad(FileManager::GetPath(_file));
	
	switch(_action)
	{
		case wa_Install:
			t.Install();
			break;
		case wa_Uninstall:
			t.Uninstall();
			break;
	}
}