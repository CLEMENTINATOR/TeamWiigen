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
        void AddItem(Libwiisys::Object* item, const std::string& text = "",
                     bool defaultValue = false);
        void AddItem(ListItemData d, bool defaultValue = false);
        void SetPosition(int x, int y);
        void DefaultImage(std::string s);
        void OverImage(std::string s);
        void InitializeComponents();
        void SetButtonText(std::string s);
        void EnsureItems();
        void UpDefaultImage(std::string image);
        void DownDefaultImage(std::string image);
        void UpClickedImage(std::string image);
        void DownClickedImage(std::string image);
        void UpOverImage(std::string image);
        void DownOverImage(std::string image);
      private:
        ListItem *_selected;
        Button _bSelected;
        List _list;
        void ShowList(Libwiisys::Object *o,
                      Libwui::Events::CursorEventArgs* args);
        void OnClickSetValue(Libwiisys::Object *o,
                             Libwui::Events::CursorEventArgs* args);
        void Draw();

    };
  }
}

#endif /* DROPDOWNLIST_HPP_ */