#ifndef _UI_COMPONENT_FORM_
#define _UI_COMPONENT_FORM_

#include "../Control.hpp"
#include "../Message.hpp"

#include <string>

namespace Libwui
{
  namespace Component
  {
    class Form : public Libwui::Control
    {
      protected:
        bool IsInUITree();
      public:
        void SetRoot(bool root, const std::string& id = "root");
        Form();
      private:
        bool isRoot;
    };
  }
}

#endif
