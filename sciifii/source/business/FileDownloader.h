#ifndef _FILE_DOWNLOADER_H_
#define _FILE_DOWNLOADER_H_

#include "common/Installer.h"


class FileDownloader : public Installer
{
private:
	std::string _file;

public:
	FileDownloader(const std::string &file);
	bool Prepare();
	void Install();
};

#endif