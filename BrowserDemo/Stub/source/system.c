// this code was taken from libogc, see http://www.devkitpro.org/ 

#include "asm.h"
#include "cache.h"
#include "system.h"
#include "processor.h"

#define NUM_EXCEPTIONS			15

#define SYSMEM1_SIZE			0x01800000
#if defined(HW_RVL)
#define SYSMEM2_SIZE			0x04000000
#endif

typedef int word;               /* "word" used for optimal copy speed */

#undef  wsize
#define wsize   sizeof(word)
#undef  wmask
#define wmask   (wsize - 1)

static u32 exception_location[NUM_EXCEPTIONS] = {
		0x00000100, 0x00000200, 0x00000300, 0x00000400,
		0x00000500, 0x00000600, 0x00000700, 0x00000800,
		0x00000900, 0x00000C00, 0x00000D00, 0x00000F00,
		0x00001300, 0x00001400, 0x00001700 };

static vu16* const _memReg = (u16*)0xCC004000;
extern void __realmode(void*);
extern void __configMEM1_24Mb();
//extern void __configMEM1_48Mb();
extern void __configMEM2_64Mb();
//extern void __configMEM2_128Mb();

void __bat_config()
{
	u32 realmem1 = SYSMEM1_SIZE;
	u32 simmem1 = SYSMEM1_SIZE;
#if defined(HW_RVL)
	u32 simmem2 = SYSMEM2_SIZE;
#endif

	if(simmem1<realmem1 && !(simmem1-0x1800000)) {
		DCInvalidateRange((void*)0x81800000,0x01800000);
		_memReg[20] = 2;
	}

	if(simmem1<=0x01800000) __realmode(__configMEM1_24Mb);

#if defined(HW_RVL)
	if(simmem2<=0x04000000) __realmode(__configMEM2_64Mb);
#endif
}

void __exception_close(u32 except)
{
	void *pAdd = (void*)(0x80000000|exception_location[except]);
	*(u32*)pAdd = 0x4C000064;
	DCFlushRangeNoSync(pAdd,0x100);
	ICInvalidateRange(pAdd,0x100);
	_sync();
}

void __exception_closeall()
{
	s32 i;
	for(i=0;i<NUM_EXCEPTIONS;i++) {
		__exception_close(i);
	}
	mtmsr(mfmsr()&~MSR_EE);
	mtmsr(mfmsr()|(MSR_FP|MSR_RI));
}

void* memmove(void *dst0,const void *src0,register int length)
{
    register char *dst = dst0;
    register const char *src = src0;
    register int t;

    if (length == 0 || dst == src)          /* nothing to do */
            goto done;

    /*
     * Macros: loop-t-times; and loop-t-times, t>0
     */
#undef  TLOOP
#define TLOOP(s) if (t) TLOOP1(s)
#undef  TLOOP1
#define TLOOP1(s) do { s; } while (--t)

    if ((unsigned long)dst < (unsigned long)src) {
            /*
             * Copy forward.
             */
            t = (int)src;   /* only need low bits */
            if ((t | (int)dst) & wmask) {
                    /*
                     * Try to align operands.  This cannot be done
                     * unless the low bits match.
                     */
                    if ((t ^ (int)dst) & wmask || length < wsize)
                            t = length;
                    else
                            t = wsize - (t & wmask);
                    length -= t;
                    TLOOP1(*dst++ = *src++);
            }
            /*
             * Copy whole words, then mop up any trailing bytes.
             */
            t = length / wsize;
            TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);
            t = length & wmask;
            TLOOP(*dst++ = *src++);
    } else {
            /*
             * Copy backwards.  Otherwise essentially the same.
             * Alignment works as before, except that it takes
             * (t&wmask) bytes to align, not wsize-(t&wmask).
             */
            src += length;
            dst += length;
            t = (int)src;
            if ((t | (int)dst) & wmask) {
                    if ((t ^ (int)dst) & wmask || length <= wsize)
                            t = length;
                    else
                            t &= wmask;
                    length -= t;
                    TLOOP1(*--dst = *--src);
            }
            t = length / wsize;
            TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);
            t = length & wmask;
            TLOOP(*--dst = *--src);
    }
done:
    return (dst0);
}

