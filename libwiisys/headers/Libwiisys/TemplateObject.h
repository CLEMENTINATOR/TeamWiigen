#ifndef SIMPLEOBJECT_H_
#define SIMPLEOBJECT_H_
#include <string>
#include <sstream>
namespace Libwiisys
{

  template<typename T>
  class TemplateObject
  {

    private:
      T _value;

    public:
      T& Value()
      {
        return _value;
      }
      TemplateObject(T val) :
          _value(val)
      {}

      std::string ToString()
      {
        std::stringstream s;
        s<<_value;
        return s.str();
      }

  };

}

#endif
