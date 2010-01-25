// this code was taken from libogc, see http://www.devkitpro.org/ 

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <gctypes.h>

void ICInvalidateRange(void *startaddress,u32 len);
void DCInvalidateRange(void *startaddress,u32 len);
void DCFlushRange(void *startaddress,u32 len);
void DCFlushRangeNoSync(void *startaddress,u32 len);

void dol_relocstart(void *dolstart);

void* memmove(void *dst0,const void *src0,register int length);
extern void _memset(void *,int,int);

extern void __exception_closeall();

#endif
