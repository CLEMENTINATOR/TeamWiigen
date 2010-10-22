#ifndef LISTITEM_H_
#define LISTITEM_H_

#include "../Control.hpp"
#include "../Message.hpp"
#include "Label.hpp"
#include "ListItemData.h"

namespace Libwui
{
  namespace Component
  {
    class ListItem: public Control
    {
      public:
        ListItem(ListItemData data);
        void InitializeComponents();
        void OverBackgroundColor(GXColor c);
		    GXColor OverBackgroundColor();
        void DefaultBackgroundColor(GXColor color);
				GXColor DefaultBackgroundColor();
        std::string Text();
		Object* Value();
      private:
        ListItemData _data;
        Label _lbl;
        GXColor _overBackgroundColor;
		    GXColor _defaultBackgroundColor;

      protected:
        void Draw();
        void ProcessMessage(Message& message);
        virtual void OnCursorEnter();
        virtual void OnCursorLeave();
    };
  }
}
#endif /* LISTITEM_H_ */
