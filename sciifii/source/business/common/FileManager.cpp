#include "FileManager.h"

using namespace std;


FileManager& FileManager::Instance()
{
  static FileManager fm;
  return fm;
}


FileManager::FileManager()
{
}

void FileManager::Init(TiXmlElement* config)
{
  TiXmlElement* child = config->FirstChildElement();
  FileManager &fm=FileManager::Instance();
  while (child!=NULL)
    {
      if (child->Type() != TiXmlElement::COMMENT)
        {
          if (string(child->Value()) != "file")
            throw Exception("Invalid file child node name", -1);

          string name = Xml::CharToStr(child->Attribute("name"));
          string url = Xml::CharToStr(child->Attribute("url"));
          string sha1url = Xml::CharToStr(child->Attribute("sha1"));
          fileObject fo=(fileObject){name,url,sha1url};
          fm._fileList.push_back(fo);


        }
      child = child->NextSiblingElement();
    }



}
