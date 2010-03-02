#ifndef TITLEPATCHER_H_
#define TITLEPATCHER_H_

#include "Title.h"
#include "TitleModule.h"
#include "Patch.h"
#include <map>

class TitlePatcher : public Title
{
private:
	std::list<const Patch*> _patchList;
	std::list<TitleModule> _moduleList;
	
	bool _tmdDirty;
	bool _tikDirty;
	u8 _titleKey[16];
	
	u64 _titleId;
	s32 _revision;

	void InsertModule(TitleModule& module, Buffer& b_tmd);
	void EncryptContent(Buffer& b,tmd_content* tmdInfo);
	void DecryptContent(Buffer& b,tmd_content* tmdInfo);
public:
	TitlePatcher(u64 titleId = 0, s32 revision = -1);
	virtual void OnTicketLoading(TitleEventArgs &processControl);
	virtual void OnTmdLoading(TitleEventArgs &processControl);
	virtual void OnContentLoading(TitleEventArgs &processControl);
	virtual void OnTicketInstalling(TitleEventArgs &processControl);
	virtual void OnTmdInstalling(TitleEventArgs &processControl);
	void AddPatch(const Patch* patch);
	void AddModule(TitleModule module);
};
#endif
