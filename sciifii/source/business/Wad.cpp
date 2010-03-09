#include "Wad.h"

#include <libutils/exception/Exception.h>
#include <libutils/system/Title.h>

#include "common/FileManager.h"

#include <iostream>

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
	string wadPath = FileManager::GetPath(_file);
	
	cout << endl << wadPath << endl;
	
	t.LoadFromWad(wadPath);
	
	cout << "Loaded!" << endl;
	
	switch(_action)
	{
		case wa_Install:
			cout << "Install!" << endl;
			t.Install();
			break;
		case wa_Uninstall:
			t.Uninstall();
			break;
	}
}