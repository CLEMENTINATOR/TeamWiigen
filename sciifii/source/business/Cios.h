#ifndef _CIOS_H_
#define _CIOS_H_

#include <string>
#include <fastdelegate.h>
#include <vector>

#include <libutils/system/SimplePatch.h>

#include "common/Installer.h"

typedef struct
{
	std::string name;
	u16 position;
} customModule;

typedef struct
{
	std::string moduleName;
	std::string url;
	std::string hash;
	u32 offset;
	u32 bss;
	std::vector<SimplePatch> handles;
} PluginDescriptor;

class Cios : public Installer
{
private:
	std::vector<customModule> _modules;
	std::vector<PluginDescriptor> _plugins;
	std::vector<Patch*> _patches;
	u32 _iosId;
	u16 _iosRevision;
	u32 _slot;
	u32 _ciosRevision;

public:
	Cios(u32 iosId, u16 iosRevision, u32 slot, u16 ciosRevision);
	bool Prepare();
	void Install();

	void AddModule(customModule descriptor);
	void AddPlugin(PluginDescriptor descriptor);
	void AddPatch(Patch* descriptor);
};
#endif
