#ifndef _NANDFILE_H_
#define _NANDFILE_H_

#include <string>

#include <ogcsys.h>

#include "File.h"
namespace Libwiisys {
	namespace IO{
	/**
	*\class NandFile
	*\see File
	*/
class NandFile : public File
{
public:
	static NandFile& Create(const std::string &fileName);
	static NandFile& Open(const std::string &fileName, u8 mode);
	static void Delete(const std::string &fileName);
	static bool Exists(const std::string &fileName);
	void Write(const Buffer& b);
	u32 Read(Buffer& b,u32 len);
	void Close();
	~NandFile();
private:
	s32 _fd;
	NandFile(s32 fd, const std::string &fileName);
	Buffer _rest;
};
}
}

#endif
