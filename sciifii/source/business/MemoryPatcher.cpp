#include "MemoryPatcher.h"
#include <libwiisys.h>
#include <gccore.h>

#define HAVE_AHBPROT (*(vu32*)0xcd800064 == 0xFFFFFFFF)
#define MEM2_PROT (*(u32*)0xd8b420A)
#define IOS_MEM_ADDRESS 0x93400000
#define IOS_MEM_ENDADDRESS 0x94000000

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;

MemoryPatcher::MemoryPatcher()
: _patchList()
{}

bool MemoryPatcher::Prepare()
{
	OnProgress("Memory patch preparation done.",1);
	return true;
}

void MemoryPatcher::AddPatch(MemoryPatch patch)
{
	_patchList.push_back(patch);
}

void MemoryPatcher::Install()
{
	if(!HAVE_AHBPROT)
		throw Exception("Use HBC 1.0.7 or higher and don't reload the IOS in order to have the AHBPROT disabled.", -1);

	u32 mem2Status = MEM2_PROT;
	MEM2_PROT =  mem2Status & 0x0000FFFF;

	for(vector<MemoryPatch>::iterator ite = _patchList.begin(); ite != _patchList.end(); ite++)
	{
		u8 *ptr = (u8 *)IOS_MEM_ADDRESS;
		while ((u32)ptr < (IOS_MEM_ENDADDRESS - (u32)(ite->pattern.Length())))
		{
			if (!memcmp(ptr, ite->pattern.Content(), ite->pattern.Length()))
			{
				memcpy(ptr, ite->patch.Content(), ite->patch.Length());
				DCFlushRange(TITLE_ROUND_DOWN(ptr, 32), TITLE_ROUND_UP(ite->patch.Length(), 32) + 32);
			}
			ptr++;
		}
	}

	MEM2_PROT = mem2Status;
	OnProgress("Running IOS patched.", 1);
}

void MemoryPatcher::SendToLog()
{
	Log::WriteLog(Log_Info,"MemoryPatcher");
}
