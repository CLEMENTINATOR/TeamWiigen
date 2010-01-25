#ifndef _FILE_SYSTEM_MANAGER_H_
#define _FILE_SYSTEM_MANAGER_H_

#include <string>
#include <libutils/Object.h>
#include "FileSystemManagerEvents.h"

class FileSystemManager : public Object
{
private:
	FileSystemManager();
	bool cut;
	std::string clipboard;

	bool PasteFile(const std::string &sourceFile, const std::string &destDirectory);
	bool PasteDirectory(const std::string &sourceDirectory, const std::string &destDirectory);

protected:
	void OnCopiing(FileSystemManagerProcessControl *processControl);
	
public:
	FileSystemManagerEvent BeforeCopiing;
	
	static FileSystemManager& Current();
	bool Cut(const std::string &path);
	void Copy(const std::string &path);
	bool Paste(const std::string &directory);
	bool Delete(const std::string &path);
	void InstallWad(const std::string &path);
	void UninstallWad(const std::string &path);

	bool CanCopy(const std::string &path);
	bool CanDelete(const std::string &path);
	bool CanCut(const std::string &path);
	bool CanPaste(const std::string &directory);
};
#endif
