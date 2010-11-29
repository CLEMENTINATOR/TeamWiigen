#ifndef DROPDOWNLIST_HPP_
#define DROPDOWNLIST_HPP_

#include "../Control.hpp"
#include "List.hpp"
#include "Button.hpp"

namespace Libwui
{
  namespace Component
  {
    class DropDownList: public Control
    {
      public:
        DropDownList();
        void AddItem(Libwiisys::Object* item, const std::string& text = "");
        void AddItem(ListItemData d);
        void DefaultImage(std::string s);
        void OverImage(std::string s);
        void InitializeComponents();
        void SetButtonText(std::string s);
        void UpDefaultImage(std::string image);
        void DownDefaultImage(std::string image);
        void UpClickedImage(std::string image);
        void DownClickedImage(std::string image);
        void UpOverImage(std::string image);
        void DownOverImage(std::string image);
		ListItem* SelectedItem();
		void SelectedItem(ListItem* item);
			
		Events::CursorEvent SelectedItemChanged;
				
	  protected:
		void EnsureItems();
		virtual void OnSelectedItemChanged(Device::PadController &c);
				
      private:
        Button _bSelected;
        List _list;
        void ToggleList(Libwiisys::Object *o, Libwui::Events::CursorEventArgs* args);
        void List_SelectedItemChanged(Libwiisys::Object *o, Libwui::Events::CursorEventArgs* args);
    };
  }
}

#endif /* DROPDOWNLIST_HPP_ */
