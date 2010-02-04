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

typedef struct
{
	u64 title;
	u16 revision;
} titleDescriptor;

class Config : public Object
{
private:
	bool _hasNetwork;

	u32 _downgradeIos;
	u16 _downgradeIosRevision;

	u32 _truchaIos;

	std::vector<ciosDesc> _corp;
	std::vector<titleDescriptor> _updateList;
	std::vector<titleDescriptor> _partialUpdateList;
	
	bool _restoreTrucha;
	bool _installCios;
	bool _installCorp;
	bool _updateSystem;
	
	Config();
	static Config& Instance();

public:
	static bool HasNetwork();

	static u32 DowngradeIos();
	static u16 DowngradeIosRevision();

	static u32 TruchaIOS();

	static std::vector<ciosDesc>& CorpConfiguration();
	static std::vector<titleDescriptor>& UpdateList();
	static std::vector<titleDescriptor>& PartialUpdateList();
	
	static bool RestoreTrucha();
	static void RestoreTrucha(const bool& value);
	
	static bool InstallCios();
	static void InstallCios(const bool& value);
	
	static bool InstallCorp();
	static void InstallCorp(const bool& value);
	
	static bool UpdateSystem();
	static void UpdateSystem(const bool& value);
};

#endif
