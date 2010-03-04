#include "FileManager.h"
#include <libutils/com/NetworkRequest.h>
#include "../../Config.h"
#include <libutils/fs/File.h>
using namespace std;


FileManager& FileManager::Instance()
{
  static FileManager fm;
  return fm;
}


FileManager::FileManager()
{}

void FileManager::Init(TiXmlElement* config)
{
  TiXmlElement* child = config->FirstChildElement();
  FileManager &fm = FileManager::Instance();
  while (child!=NULL)
    {
      if (child->Type() != TiXmlElement::COMMENT)
        {
          if (string(child->Value()) != "file")
            throw Exception("Invalid file child node name", -1);

          string key = Xml::CharToStr(child->Attribute("key"));
          string url = Xml::CharToStr(child->Attribute("url"));
          string sha1 = Xml::CharToStr(child->Attribute("sha1"));
          string path = Xml::CharToStr(child->Attribute("path"));

          if (key.length() == 0)
            throw Exception("The file key must be provided", -1);

          if (path.length() == 0)
            path = Config::WorkingDirectory() + "/" + key;

          if (fm._fileList.find(key) != fm._fileList.end())
            throw Exception("The file descirption has already been registered", -1);

          fileObject fo = (fileObject){url, sha1, path};

          fm._fileList.insert(pair<string,fileObject>(key, fo));
        }
      child = child->NextSiblingElement();
    }

}

bool FileManager::Download(const std::string& fileKey)
{
  map<string,fileObject>::iterator ite = Instance()._fileList.find(fileKey);

  if (ite == Instance()._fileList.end())
    throw Exception("File key not defined", -1);

  fileObject fo = ite->second;

  if(!File::Exists(fo.path))
  {
	try
	{
	  NetworkRequest req(fo.url);
	  Buffer response = req.GetResponse(fo.sha1);

	  File &file = File::Create(fo.path);
	  file.Write(response);
	  file.Close();
	  delete &file;
	}
	catch(...)
	{
		return false;
	}
  }

  return true;
}

Buffer FileManager::GetFile(const std::string& fileKey)
{
  map<string,fileObject>::iterator ite = Instance()._fileList.find(fileKey);

  if (ite == Instance()._fileList.end())
    throw Exception("File key not defined!", -1);

  fileObject fo = ite->second;

  return File::ReadToEnd(fo.path);
}