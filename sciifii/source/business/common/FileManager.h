#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include <libwiisys.h>


#include <map>

typedef struct
{
	std::string url;
	std::string sha1;
	std::string path;
} fileObject;

class FileManager : public Libwiisys::Object
{
public :
	static void Init(TiXmlElement* config);
	static bool Download(const std::string& fileKey);
	static Libwiisys::Buffer GetFile(const std::string& fileKey);
	static std::string GetPath(const std::string& fileKey);
private :
	static FileManager& Instance();
	FileManager();
	std::map<std::string, fileObject> _fileList;
};



#endif
