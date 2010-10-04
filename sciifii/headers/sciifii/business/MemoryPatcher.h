#ifndef MEMORYPATCHER_H_
#define MEMORYPATCHER_H_

#include <libwiisys.h>
#include <vector>
#include "common/Installer.h"

typedef struct
{
	Libwiisys::Buffer pattern;
	Libwiisys::Buffer patch;
} MemoryPatch;

class MemoryPatcher : public Installer
{
private:
	std::vector<MemoryPatch> _patchList;
public:
	MemoryPatcher();
	void AddPatch(MemoryPatch patch);
	bool Prepare();
	void Install();
	void SendToLog();
};

#endif
