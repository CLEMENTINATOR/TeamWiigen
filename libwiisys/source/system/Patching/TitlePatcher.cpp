#include <libwiisys.h>
#include <malloc.h>
#include <limits.h>

using namespace std;
using namespace Libwiisys::System::Patching;
using namespace Libwiisys::System::Event;
using namespace Libwiisys::Exceptions;

TitlePatcher::TitlePatcher(u64 titleId, s32 revision,bool fakeSign) :
	_patchList(), _moduleList(), _tmdDirty(false), _tikDirty(false), _titleId(
			titleId), _revision(revision),_fakeSign(fakeSign) {
}

void TitlePatcher::AddPatch(const Patch* patch) {
	_patchList.push_back(patch);
}

void TitlePatcher::AddModule(TitleModule module) {
	_moduleList.push_back(module);
}

void TitlePatcher::OnTmdLoading(TitleEventArgs &processControl) {
	if (_revision > -1) {
		tmd *p_tmd = (tmd*) SIGNATURE_PAYLOAD(
				(signed_blob*) processControl.buffer.Content());
		p_tmd->title_version = _revision;
		_tmdDirty = true;
	}

	if (_titleId != 0) {
		tmd *p_tmd = (tmd*) SIGNATURE_PAYLOAD(
				(signed_blob*) processControl.buffer.Content());
		p_tmd->title_id = _titleId;
		_tmdDirty = true;
	}

	Title::OnTmdLoading(processControl);
}

void TitlePatcher::InsertModule(TitleModule& module, Buffer& b_tmd) {
	signed_blob* oldTmd = (signed_blob*) b_tmd.Content();
	u32 newTmdLen = SIGNED_TMD_SIZE(oldTmd) + sizeof(tmd_content);
	signed_blob* newTmd = (signed_blob*) malloc(newTmdLen);
	if (!newTmd)
		throw Exception("Not enough memory!", -1);

	//copy the old TMD
	memset(newTmd, 0, newTmdLen);
	memcpy(newTmd, oldTmd, SIGNED_TMD_SIZE(oldTmd));

	tmd* tmd_data = (tmd *) SIGNATURE_PAYLOAD(newTmd);
	tmd_content* newEntry = &(tmd_data->contents[tmd_data->num_contents]);

	/* Find free CID and index */
	for (u32 cnt = 0; cnt < tmd_data->num_contents; cnt++) {
		tmd_content *content = &(tmd_data->contents[cnt]);

		/* Compare CID */
		if (newEntry->cid <= content->cid)
			newEntry->cid = content->cid + 1;

		/* Compare index */
		if (newEntry->index <= content->index)
			newEntry->index = content->index + 1;
	}

	/* Set content info */
	newEntry->type = 1;
	newEntry->size = module.Length();

	/* Update TMD */
	if (module.IsPositionRequired()) {
		tmd_content oldEntry = tmd_data->contents[module.Position()];
		tmd_data->contents[module.Position()]
				= tmd_data->contents[tmd_data->num_contents];
		tmd_data->contents[tmd_data->num_contents] = oldEntry;
		newEntry = &(tmd_data->contents[module.Position()]);
	}

	Buffer copyModule(module);
	EncryptContent(copyModule, newEntry);
	AddContent(copyModule, newEntry->cid);

	tmd_data->num_contents++;
	b_tmd.Clear();
	b_tmd.Append(newTmd, newTmdLen);

	free(newTmd);
}

void TitlePatcher::OnContentLoading(TitleEventArgs &processControl) {
	DecryptContent(processControl.buffer, processControl.tmdInfo);
	for (list<const Patch*>::const_iterator ite = _patchList.begin(); ite
			!= _patchList.end(); ite++)
		if ((*ite)->ApplyPatch(processControl) > 0) {
			processControl.tmdInfo->type = 1;
			_tmdDirty = true;
		}

	EncryptContent(processControl.buffer, processControl.tmdInfo);

	Title::OnContentLoading(processControl);
}

void TitlePatcher::OnTicketLoading(TitleEventArgs &processControl) {
	DecryptTitleKey(processControl.buffer);
	Title::OnTicketLoading(processControl);
}

void TitlePatcher::OnTicketInstalling(TitleEventArgs &processControl) {
	if(!_fakeSign) return;
	if (_tikDirty) {
		signed_blob* s_tik = (signed_blob*) processControl.buffer.Content();

		/* Zero signature */
		memset((u8*) s_tik + 4, 0, SIGNATURE_SIZE(s_tik) - 4);

		/* TIK data */
		tik *p_tik = (tik *) SIGNATURE_PAYLOAD(s_tik);

		for (u16 fill = 0; fill < USHRT_MAX; fill++) {
			sha1 hash;

			p_tik->padding = fill;

			SHA1((u8 *) p_tik, sizeof(tik), hash);

			if (!hash[0]) {
				Title::OnTicketInstalling(processControl);
				return;
			}
		}

		throw Exception("Error fake signing the Ticket.", -1);
	}
}

void TitlePatcher::OnTmdInstalling(TitleEventArgs &processControl) {
	for (list<TitleModule>::iterator ite = _moduleList.begin(); ite
			!= _moduleList.end(); ite++) {
		_tmdDirty = true;
		InsertModule(*ite, processControl.buffer);
	}
	if(!_fakeSign) return;
	if (_tmdDirty) {
		signed_blob* s_tmd = (signed_blob*) processControl.buffer.Content();

		/* Zero signature */
		memset((u8*) s_tmd + 4, 0, SIGNATURE_SIZE(s_tmd) - 4);

		/* TMD data */
		tmd *tmd_data = (tmd *) SIGNATURE_PAYLOAD(s_tmd);

		for (u16 fill = 0; fill < USHRT_MAX; fill++) {
			sha1 hash;

			/* Modify TMD fill field */
			tmd_data->fill3 = fill;

			/* Calculate hash */
			SHA1((u8 *) tmd_data, TMD_SIZE(tmd_data), hash);

			/* Found valid hash */
			if (!hash[0]) {
				Title::OnTmdInstalling(processControl);
				return;
			}
		}

		throw Exception("Error fake signing the TMD.", -1);
	}
}

void TitlePatcher::DecryptTitleKey(Buffer& b_tik) {
	Title::DecryptTitleKey(b_tik);
	/* Change title id*/
	if (_titleId != 0) {
		tik* p_tik = (tik*) SIGNATURE_PAYLOAD((signed_blob*) b_tik.Content());
		u8 iv[16] ATTRIBUTE_ALIGN(32);
		u8 enc[16] ATTRIBUTE_ALIGN(32);
		u8 dec[16] ATTRIBUTE_ALIGN(32);
		memcpy(dec, _titleKey, sizeof(_titleKey));
		p_tik->titleid = _titleId;
		memset(iv, 0, sizeof(iv));
		memcpy(iv, &p_tik->titleid, sizeof(u64));
		AES_Encrypt(iv, dec, enc, sizeof(dec));
		memcpy(p_tik->cipher_title_key, enc, sizeof(enc));
		_tikDirty = true;
	}

}

std::string TitlePatcher::GetType()
{
	return "Libwiisys::System::Patching::TitlePatcher,"+Title::GetType();
}

