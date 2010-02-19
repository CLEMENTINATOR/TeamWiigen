#include "WadBatchInstaller.h"

#include <vector>
#include <libutils/system/Title.h>
#include <libutils/fs/File.h>
#include <libutils/fs/Directory.h>
#include <libutils/fs/Path.h>

using namespace std;

WadBatchInstaller::WadBatchInstaller(const string& folder)
: _wadFolder(folder)
{}

bool WadBatchInstaller::Prepare()
{
	return true;
}

void WadBatchInstaller::Install()
{
	vector<string> files = Directory::GetFiles(_wadFolder);
	u32 steps = files.size();
	f32 currentStep = 0;

	for(vector<string>::iterator ite = files.begin(); ite != files.end(); ite++)
	{
		Title wad;
		string fileName = Path::GetFileName(*ite);

		OnProgress("Loading " + fileName, currentStep / steps);
		wad.LoadFromWad(*ite);

		OnProgress("Install " + fileName, (currentStep + 0.5) / steps);
		wad.Install();

		currentStep++;
	}
}
