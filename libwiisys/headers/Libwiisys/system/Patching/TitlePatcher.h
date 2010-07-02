#ifndef TITLEPATCHER_H_
#define TITLEPATCHER_H_

#include <list>

#include "../Title.h"
#include "Patch.h"
#include "TitleModule.h"

namespace Libwiisys { namespace System { namespace Patching {

class TitlePatcher : public Title
{
private:
	std::list<const Patch*> _patchList;
	std::list<TitleModule> _moduleList;

	bool _tmdDirty;
	bool _tikDirty;


	u64 _titleId;
	s32 _revision;
    virtual void DecryptTitleKey(Buffer& b_tik);
	void InsertModule(TitleModule& module, Buffer& b_tmd);
public:
	TitlePatcher(u64 titleId = 0, s32 revision = -1);
	virtual void OnTicketLoading(Event::TitleEventArgs &processControl);
	virtual void OnTmdLoading(Event::TitleEventArgs &processControl);
	virtual void OnContentLoading(Event::TitleEventArgs &processControl);
	virtual void OnTicketInstalling(Event::TitleEventArgs &processControl);
	virtual void OnTmdInstalling(Event::TitleEventArgs &processControl);
	void AddPatch(const Patch* patch);
	void AddModule(TitleModule module);
};

}}}
#endif