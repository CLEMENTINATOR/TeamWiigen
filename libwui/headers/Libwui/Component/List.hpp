#ifndef _LIST_H_
#define _LIST_H_

#include <vector>
#include <libwiisys/Object.h>
#include "../Control.hpp"
#include "../Message.hpp"
#include "ListItem.h"
#include "ListItemData.h"
#include "Button.hpp"

namespace Libwui
{
  namespace Component
  {
    class List: public Control
    {
      public:
        void AddItem(Libwiisys::Object* item, const std::string& text = "");
        void AddItem(ListItemData d);
        void AddItem(ListItem* i);
        void InitializeComponents();
        void UpDefaultImage(std::string image);
        void DownDefaultImage(std::string image);
        void UpClickedImage(std::string image);
        void DownClickedImage(std::string image);
        void UpOverImage(std::string image);
        void SetSize(s32 w, s32 h);
        void DownOverImage(std::string image);
      private:
        std::vector<ListItem*> _items;
        Button _bScrollUp;
        Button _bScrollDown;
        virtual void Draw();
        u32 _selectedIndex;
        u32 _maxItemsShowable;

      protected:
        void EnsureItems();
        void Invalidate();
        void ScrollDown(Libwiisys::Object* sender,
                        Libwui::Events::CursorEventArgs* args);
        void ScrollUp(Libwiisys::Object* sender,
                      Libwui::Events::CursorEventArgs* args);
    };
  }
}
#endif
