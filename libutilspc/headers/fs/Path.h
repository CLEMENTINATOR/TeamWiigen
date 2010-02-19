#ifndef _PATH_H_
#define _PATH_H_

#include "../Object.h"
#include <string>

class Path : public Object
{
public:
	static std::string GetRoot(const std::string &path);
	static std::string GetRootName(const std::string &path);
	static std::string GetParentDirectory(const std::string &path);
	static std::string GetFileName(const std::string &path);
	static std::string GetFileNameWithoutExtension(const std::string &path);
	static std::string GetFileExtension(const std::string &path);
	static std::string CleanPath(const std::string &path);
};

#endif
