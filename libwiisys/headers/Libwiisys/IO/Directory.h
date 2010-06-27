#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include "../Object.h"
#include <string>
#include <vector>

namespace Libwiisys {  namespace IO{
/**
 *\class Directory
 *\brief Represents a directory
 * \author Arasium, Teton, Fanta
 * \version 1.0
**/
class Directory : public Object
{
public:
	static void Create(const std::string &name);
	static void Delete(const std::string &name, bool recursive = false);
	static void Copy(const std::string &name, const std::string &dest, bool recursive = false);
	static void Move(const std::string &name, const std::string &dest);
	static bool Exists(const std::string &name);
	static std::vector<std::string> GetFiles(const std::string &name);
	static std::vector<std::string> GetDirectories(const std::string &name);
	static bool IsEmpty(const std::string &name);
private:
	static std::string CleanPath(const std::string &path);
};
}
}
#endif
