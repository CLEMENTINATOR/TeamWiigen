#include "WadBatch.h"

#include <vector>
#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::System;
using namespace Libwiisys::Logging;


WadBatch::WadBatch(const string& folder,TitleAction action)
: _wadFolder(folder),a(action)
{}

bool WadBatch::Prepare()
{
	return true;
}

void WadBatch::Install()
{
	vector<string> files = Directory::GetFiles(_wadFolder);
	u32 steps = files.size();
	f32 currentStep = 0;

	for(vector<string>::iterator ite = files.begin(); ite != files.end(); ite++)
	{
		Title wad;
		string fileName = Path::GetFileName(*ite);
        if(Path::GetFileExtension(*ite)!="wad")
        {
        currentStep++;
        continue;
        }
		OnProgress("Loading " + fileName, currentStep / steps);
		wad.LoadFromWad(*ite);
    if(a==ti_Install)
    {
		OnProgress("Install " + fileName, (currentStep + 0.5) / steps);
		wad.Install();
    }
    else if (a==ti_Uninstall)
    {
        OnProgress("Uninstall " + fileName, (currentStep + 0.5) / steps);
		wad.Uninstall();
    }

		currentStep++;
	}
}

void WadBatch::SendToLog()
{
Log::WriteLog(Log_Info,"WadBatch("+_wadFolder+")");
}

