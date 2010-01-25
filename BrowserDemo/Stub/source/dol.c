// this code was contributed by shagkur of the devkitpro team, thx!

#include "asm.h"
#include "processor.h"
#include "system.h"
#include "dol.h"
#include "debug.h"

typedef struct _dolheader {
	u32 text_pos[7];
	u32 data_pos[11];
	u32 text_start[7];
	u32 data_start[11];
	u32 text_size[7];
	u32 data_size[11];
	u32 bss_start;
	u32 bss_size;
	u32 entry_point;
} dolheader;

typedef void (*entrypoint) (void);

void dol_relocstart (void *dolstart) {
	u32 i,level;
	entrypoint entry_p;
	dolheader *dolfile;

	if (dolstart) {
		dolfile = (dolheader *) dolstart;
		for (i = 0; i < 7; i++) {
			if ((!dolfile->text_size[i]) ||
                            (dolfile->text_start[i] < 0x100))
                                continue;

			ICInvalidateRange ((void *) dolfile->text_start[i],
                                                    dolfile->text_size[i]);
			memmove ((void *) dolfile->text_start[i],
                                 dolstart+dolfile->text_pos[i],
                                 dolfile->text_size[i]);
		}

		for(i = 0;i < 11; i++) {
			if ((!dolfile->data_size[i]) ||
                            (dolfile->data_start[i] < 0x100))
                                continue;


			memmove ((void*) dolfile->data_start[i],
                                 dolstart+dolfile->data_pos[i],
                                 dolfile->data_size[i]);
			DCFlushRangeNoSync ((void *) dolfile->data_start[i],
                                            dolfile->data_size[i]);
		}

		_memset ((void *) dolfile->bss_start, 0, dolfile->bss_size);
		DCFlushRange((void *) dolfile->bss_start, dolfile->bss_size);

		entry_p = (entrypoint) dolfile->entry_point;

		_CPU_ISR_Disable (level);
		__exception_closeall ();
		entry_p ();
		_CPU_ISR_Restore (level);
	}
}

