#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <gctypes.h>
#include <string>

typedef struct
{
	u32 destId;
	u32 sourceId;
	u16 revision;
	u8 dipVersion;
	u8 esVersion;
	bool IdentifyPatch;
	bool NandPatch;
	bool KoreanPatch;
	std::string wadSource;
} ciosDesc;

extern bool allowIllegal;

extern ciosDesc installCioses[];

extern const u64 NB_INSTALL_CIOS;

extern bool hasNetwork;

extern u16 ios15Revision;

void ConfigureSciifii();

#endif
