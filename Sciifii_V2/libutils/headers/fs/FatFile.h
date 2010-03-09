#ifndef _FATFILE_H_
#define _FATFILE_H_

#include <string>
#include <stdio.h>

#include <ogcsys.h>

#include "File.h"
#include "Device.h"

class FatFile : public File
{
public:
	static FatFile& Create(const std::string &fileName);
	static FatFile& Open(const std::string &fileName, const std::string &mode);
	static void Delete(const std::string &fileName);
	static bool Exists(const std::string &fileName);
	void Write(const Buffer& b);
	u32 Read(Buffer& b,u32 len);
	void Close();
	~FatFile();
private:
	FILE *_fd;
	FatFile(FILE *fd, const std::string &fileName);
};

#endif
