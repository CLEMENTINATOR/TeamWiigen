#include "MemoryPatcher.h"
#include <libwiisys.h>
#include <gccore.h>

#define HAVE_AHBPROT (*(vu32*)0xcd800064 == 0xFFFFFFFF)
#define MEM2_PROT (*(u32*)0xd8b420A)

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;

bool MemoryPatcher::Prepare()
{
	OnProgress("Memory patch preparation done.",1);
	return true;
}

void MemoryPatcher::Install()
{
	if(!HAVE_AHBPROT)
		throw Exception("Use HBC 1.0.7 or higher and don't reload the IOS in order to have the AHBPROT disabled.", -1);
	u32 mem2Status = MEM2_PROT;
	MEM2_PROT =  mem2Status & 0x0000FFFF;

	//for each patch

	MEM2_PROT = mem2Status;
}

void MemoryPatcher::SendToLog()
{
	Log::WriteLog(Log_Info,"MemoryPatcher");
}
