#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <gctypes.h>
#include <string>
#include <libutils/Object.h>
#include <vector>

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

class Config : public Object
{
private:
	bool _hasNetwork;

	u32 _downgradeIos;
	u16 _downgradeIosRevision;

	u32 _truchaIos;

	std::vector<ciosDesc> _corp;

	Config();
	static Config& Instance();

public:
	static bool HasNetwork();

	static u32 DowngradeIos();
	static u16 DowngradeIosRevision();

	static u32 TruchaIOS();

	static std::vector<ciosDesc>& CorpConfiguration();
};

#endif
