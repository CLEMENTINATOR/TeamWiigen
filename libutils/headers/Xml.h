#ifndef _UTILS_XML_H
#define _UTILS_XML_H

#include <string>
#include <tinyxml.h>
/**
*\class Xml
*\brief Loads XML Files (tinyxml needed !)
*\author Arasium,Teton,Fanta
*\version 1.0
*/
class Xml
  {
  public:
    static TiXmlDocument& Load(const std::string &file);
  };

#endif
