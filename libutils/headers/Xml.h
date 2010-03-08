#ifndef _UTILS_XML_H
#define _UTILS_XML_H

#include <string>
#include <tinyxml.h>

class Xml
  {
  public:
    static TiXmlDocument& Load(const std::string &file);
  };

#endif
