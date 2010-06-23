#ifndef _TITLE_H_
#define _TITLE_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include "../Object.h"
#include "event/TitleEvent.h"
#include "event/TitleEventArgs.h"
#include "security/Identification.h"

#define TITLE_BLOCK_SIZE 1000

#define TITLE_ROUND_UP(x,n)	(-(-(x) & -(n)))

#define INIT_PROCESS_CONTROL(p, s) p.tmdInfo = s;\
		p.skipStep = false;\
		p.abortProcess = false;
/**
*\struct ATTRIBUTE_PACKED wad_header
*\brief Struct representing a wad header
**/
namespace Libwiisys { namespace System {
typedef struct {
	/** Header length */
	u32 header_len;

	/** WAD type */
	char type[2];

	/** Padding data */
	u16 padding;

	/** Data length */
	u32 certs_len, crl_len, tik_len, tmd_len, data_len, footer_len;
} ATTRIBUTE_PACKED wad_header;


/*! \class Title
 * \brief This class allow all the Title utilisation.
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * The Title class allow the user to install/unistall/load from Nus serv or a WAD file.
 */

inline u32 TITLE_ID(u64 title) { return (u32)title; }
inline u32 TITLE_TYPE(u64 title) { return title >> 32; }
inline bool IS_IOS(u64 title) { return (title & 0x100000000ULL) > 0; }

class Title : public Object
{
protected:
	virtual void OnTicketInstalling(Event::TitleEventArgs &processControl);
	virtual void OnTicketInstalled(Event::TitleEventArgs &processControl);
	virtual void OnTmdInstalling(Event::TitleEventArgs &processControl);
	virtual void OnTmdInstalled(Event::TitleEventArgs &processControl);
	virtual void OnContentInstalling(Event::TitleEventArgs &processControl);
	virtual void OnContentInstalled(Event::TitleEventArgs &processControl);

	virtual void OnTicketLoading(Event::TitleEventArgs &processControl);
	virtual void OnTicketLoaded(Event::TitleEventArgs &processControl);
	virtual void OnTmdLoading(Event::TitleEventArgs &processControl);
	virtual void OnTmdLoaded(Event::TitleEventArgs &processControl);
	virtual void OnContentLoading(Event::TitleEventArgs &processControl);
	virtual void OnContentLoaded(Event::TitleEventArgs &processControl);

	void Ticket(const Buffer& buffer);
	Buffer Ticket();
	void Tmd(const Buffer& buffer);
	Buffer Tmd();
	void Certificate(const Buffer& buffer);
	Buffer Certificate();
	void Crl(const Buffer& buffer);
	Buffer Crl();
	void AddContent(const Buffer& buffer, u32 id);
	Buffer GetContent(u32 id);

    void EncryptContent(Buffer& b,tmd_content* tmdInfo);
	void DecryptContent(Buffer& b,tmd_content* tmdInfo);
	u8 _titleKey[16];
	virtual void DecryptTitleKey(Buffer& b_tik);
	Buffer GetSharedContent(tmd_content* c);


public:
	static void ReloadIOS(u32 ios);
	static u32 GetRunningIOS();
    void SaveDecryptedContent(const std::string& dirPath);
	Title(bool automaticCleaning = true);
	void LoadFromWad(const std::string& file, const std::string& tempFolder = "sd:/tmp");
	void LoadFromNand(u64 titleId, const std::string& tempFolder = "sd:/tmp");
	void LoadFromNusServer(u64 titleId, u16 revision = 0, const std::string& tempFolder = "sd:/tmp");
	void PackAsWad(const std::string& fileName);
	static std::vector<u8> GetInstalledIos();
	static std::string GetWadFormatedName(u64 tid,u16 rev);
	static u16 GetInstalledTitleVersion(u64 titleId);
	void Install();
	void Uninstall();
	static void Uninstall(u64 titleId);
	bool IsInstalled();
	static bool IsInstalled(u64 titleId);
	void Clean();
	void CreateTempDirectory(u64 titleId, u16 revision, const std::string& tempDirectory);
	std::string TempDirectory();
	~Title();

	//Events
	Event::TitleEvent TicketInstallingEvent;
	Event::TitleEvent TicketInstalledEvent;
	Event::TitleEvent TmdInstallingEvent;
	Event::TitleEvent TmdInstalledEvent;
	Event::TitleEvent ContentInstallingEvent;
	Event::TitleEvent ContentInstalledEvent;
	Event::TitleEvent TicketLoadingEvent;
	Event::TitleEvent TicketLoadedEvent;
	Event::TitleEvent TmdLoadingEvent;
	Event::TitleEvent TmdLoadedEvent;
	Event::TitleEvent ContentLoadingEvent;
	Event::TitleEvent ContentLoadedEvent;
private:
	u32 _tikLen;
	u32 _tmdLen;
	u64 _titleId;
	u16 _revision;
	u32 _dataLen;

	std::string _directory;
	bool automaticClean;
	bool canDeleteRootTempDirectory;

	Buffer GetTitleElementFromTemp(const std::string &path);
	static void UninstallUsingISFS(u64 titleId);
};
}
}
#endif