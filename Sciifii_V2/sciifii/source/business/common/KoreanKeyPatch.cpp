#include "KoreanKeyPatch.h"

#include <string.h>
#include "../../../build/kkey_dat.h"

u32 KoreanKeyPatch::Patching(TitleEventArgs &processControl) const
{
	u32 match_count = 0;
	const u8 koreankey_data[] = { 0x27, 0xB8, 0xA5, 0xF2, 0x00, 0x00, 0x00, 0x00 };
	const u16 patchSize = 0x30 + kkey_dat_size;
	//kkey patch part two - default kkey is all zeros, so insert actual kkey into IOS
	for (u32 cnt = 0; cnt < processControl.buffer.Length() - patchSize; cnt++) 
	{
		u8 *ptr = (u8*)processControl.buffer.Content() + cnt;
		
		if (!memcmp(ptr, koreankey_data, sizeof(koreankey_data)))
		{
			memcpy (ptr + 0x30, kkey_dat, kkey_dat_size);
			cnt += patchSize;
			match_count++;
		}
	}
	return match_count;
}
