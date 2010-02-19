#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include "../Object.h"
#include <string>
#include <vector>

class Directory : public Object
{
public:
	static void Create(const std::string &name);
	static void Delete(const std::string &name, bool recursive = false);
	static bool Exists(const std::string &name);
	static std::vector<std::string> GetFiles(const std::string &name);
	static std::vector<std::string> GetDirectories(const std::string &name);
	static bool IsEmpty(const std::string &name);
private:
	static std::string CleanPath(const std::string &path);
};

#endif
