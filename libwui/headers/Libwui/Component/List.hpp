#ifndef _LIST_H_
#define _LIST_H_

#include <vector>
#include <Libwiisys/Object.h>
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
		List();
		virtual ~List();
        void AddItem(Libwiisys::Object* item, const std::string& text = "");
        void AddItem(const ListItemData& d);
        void AddItem(const ListItem& i);
        void InitializeComponents();
        void UpDefaultImage(std::string image);
        void DownDefaultImage(std::string image);
        void UpClickedImage(std::string image);
        void DownClickedImage(std::string image);
        void UpOverImage(std::string image);
		void DownOverImage(std::string image);
        void SetSize(s32 w, s32 h);
		const std::vector<ListItem*>& Items();
		ListItem* SelectedItem();
		void SelectedItem(ListItem* item);
		bool RenderAsDropDown;
		Events::CursorEvent SelectedItemChanged;
				
      private:
        std::vector<ListItem*> _items;
        Button _bScrollUp;
        Button _bScrollDown;
        u32 _startShowIndex;
        u32 _maxItemsShowable;
		ListItem* _selectedItem;
			
		void ItemClicked(Object *sender, Libwui::Events::CursorEventArgs* args);

      protected:
		void OnSelectedItemChanged(Device::PadController &c);
        void EnsureItems();
        void ScrollDown(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
        void ScrollUp(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
    };
  }
}
#endif
