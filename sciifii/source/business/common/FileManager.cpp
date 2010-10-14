#include <sstream>
#include <sciifii/business/common/FileManager.h>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Path.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <sciifii/Config.h>
#include <Libwiisys/Network/HttpRequest.h>
#include <Libwiisys/String/UtilString.h>
#include <Libwiisys/logging/Log.h>

using namespace std;

using namespace Libwiisys;
using namespace Libwiisys::Network;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;

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
        throw Exception("Invalid file child node name");

      string key = UtilString::ToStr(child->Attribute("key"));
      string url = UtilString::ToStr(child->Attribute("url"), "");
      string sha1 = UtilString::ToStr(child->Attribute("sha1"), "");
      string path = UtilString::ToStr(child->Attribute("path"), "");

      if (key.length() == 0)
        throw Exception("The file key must be provided");

      if (path.length() == 0)
        path = Config::WorkingDirectory() + "/" + key;

      if (fm._fileList.find(key) != fm._fileList.end())
        throw Exception("The file descirption has already been registered");

      fileObject fo = (fileObject)
                      {
                        url, sha1, path
                      };

      fm._fileList.insert(pair<string,fileObject>(key, fo));



    }
    child = child->NextSiblingElement();
  }

}

bool FileManager::Download(const std::string& fileKey)
{
  map<string,fileObject>::iterator ite = Instance()._fileList.find(fileKey);

  if (ite == Instance()._fileList.end())
    throw Exception("File key not defined");

  fileObject fo = ite->second;

  stringstream str;
  str<<"File("<<fileKey<<","<<fo.url<<","<<fo.sha1<<","<<fo.path<<")";
  Log::WriteLog(Log_Info,str.str());

  if(!File::Exists(fo.path) && fo.url != "")
  {
    try
    {
      HttpRequest req(fo.url);
      Buffer response = req.GetResponse(fo.sha1);

      if(Path::GetParentDirectory(fo.path) != "")
        Directory::Create(Path::GetParentDirectory(fo.path));

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
  else if(fo.url == "")
    return false;

  return true;
}

Buffer FileManager::GetFile(const std::string& fileKey)
{
  map<string,fileObject>::iterator ite = Instance()._fileList.find(fileKey);

  if (ite == Instance()._fileList.end())
  {
    if(!File::Exists(Config::WorkingDirectory() + "/" + fileKey))
      throw Exception("File key not defined and file ot found in working directory!");

    return File::ReadToEnd(Config::WorkingDirectory() + "/" + fileKey);
  }

  return File::ReadToEnd(ite->second.path);
}

string FileManager::GetPath(const std::string& fileKey)
{
  map<string,fileObject>::iterator ite = Instance()._fileList.find(fileKey);

  if (ite == Instance()._fileList.end())
  {
    if(!File::Exists(Config::WorkingDirectory() + "/" + fileKey))
      throw Exception("File key not defined and file ot found in working directory!");

    return Config::WorkingDirectory() + "/" + fileKey;
  }

  return ite->second.path;
}
