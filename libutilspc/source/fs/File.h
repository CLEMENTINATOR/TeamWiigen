#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include <ogcsys.h>
#include "../Object.h"
#include "../com/Buffer.h"

typedef enum
{
	FileMode_Read,
	FileMode_Write,
	FileMode_ReadWrite,
} FileMode;

class File : public Object
{
protected:
	std::string _fileName;
	u32 _fileLength;

public:
	static File& Create(const std::string &fileName);
	static File& Open(const std::string &fileName, FileMode mode);
	static void Delete(const std::string &fileName);
	static bool Exists(const std::string &fileName);
	static Buffer ReadToEnd(const std::string &fileName);
	virtual void Write(const Buffer& b) = 0;
	virtual u32 Read(Buffer& b,u32 len) = 0;
	virtual void Close() = 0;
	u32 Size() const;
	virtual ~File() = 0;
};

#endif
