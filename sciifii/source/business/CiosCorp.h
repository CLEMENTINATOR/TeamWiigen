#ifndef CIOSCORP_H_
#define CIOSCORP_H_

#include <string>
#include <fastdelegate.h>
#include <libutils/Object.h>
#include <vector>
#include <map>

#include "common/Installer.h"

typedef struct
{
	u64 destId;
	u64 sourceId;
	u16 revision;
	std::vector<std::string> modules;
	bool IdentifyPatch;
	bool NandPatch;
	bool KoreanPatch;
	bool localOnly;
} ciosDesc;

typedef struct
{
	std::string module;
	std::string file;
} moduleDesc;

class CiosCorp : public Installer
{
private:
	std::vector<ciosDesc> _items;
	std::map<std::string, moduleDesc> _modules;
	
public:
	bool Prepare();
	void Install();
	void SendToLog();
	void AddModule(const std::string& name, const moduleDesc& module);
	void AddItem(const ciosDesc& item);
};
#endif
