#include <gccore.h>
#include "string.h"
#include "../../Memory.h"

extern u8  stub_bin[];
extern u32 stub_bin_size;
extern u8  Browser_dol[];
extern u32 Browser_dol_size;

void (*stubIt) () = (void (*) ()) STUB_MEM_ADDR;

int main(int argc, char **argv)
{
	memcpy ((void *) STUB_MEM_ADDR, stub_bin, stub_bin_size);
    DCFlushRange ((void *) STUB_MEM_ADDR, stub_bin_size);

	memcpy ((void *) BROWSER_DOL_MEM_ADDR, Browser_dol, Browser_dol_size);
    DCFlushRange ((void *) BROWSER_DOL_MEM_ADDR, Browser_dol_size);

	__IOS_ShutdownSubsystems();
	stubIt();

	return 0;
}

