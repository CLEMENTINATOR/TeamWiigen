#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include <libutils/Xml.h>
#include <libutils/com/Buffer.h>
#include <vector>
#include <libutils/exception/Exception.h>
typedef struct
{
	std::string name;
	std::string url;
	std::string sha1url;

} fileObject;

class FileManager : public Object{


public :
static void Init(TiXmlElement* config);
static bool Download(const std::string& fileKey);
static Buffer GetFile(const std::string& fileKey);

private :
static FileManager& Instance();
FileManager();
std::vector<fileObject> _fileList;



};



#endif
