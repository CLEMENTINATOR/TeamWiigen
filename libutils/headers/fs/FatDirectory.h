#ifndef _FATDIRECTORY_H_
#define _FATDIRECTORY_H_

#include "../Object.h"
#include <string>
#include <vector>

/**
*\class FatDirectory
*\see Directory
*/
class FatDirectory : public Object
{
public:
	static void Create(const std::string &name);
	static void Delete(const std::string &name);
	static bool Exists(const std::string &name);
	static std::vector<std::string> GetFiles(const std::string & path);
	static std::vector<std::string> GetDirectories(const std::string & path);
};

#endif
