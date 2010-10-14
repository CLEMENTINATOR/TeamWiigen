#ifndef MESSAGEBOX_HPP_
#define MESSAGEBOX_HPP_

#include "../Control.hpp"
#include "Image.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "TextAera.h"
#include "Form.hpp"

namespace Libwui
{
  namespace Component
  {
    class MessageBox: public Form
    {
      public:
        MessageBox();
        void InitializeComponents();
        void Show(Control* _current, std::string text, std::string title);
        void SetTextSize(int x, int y);
        void SetTitlePosition(int x, int y);
        void SetTitleSize(int x, int y);
        void SetTextPosition(int x, int y);
        void SetButtonPosition(int x, int y);
        void SetMessageBoxImage(std::string s);
        void DefaultButtonImage(std::string s);
        void OverButtonImage(std::string s);
        void ClickedButtonImage(std::string s);
      private:
        void Hide();
        void Button_Clicked(Libwiisys::Object*sender, Events::CursorEventArgs *c);
        Image _boxImg;
        Button _boxButton;
        Label _title;
        TextAera _text;
    };
  }
}

#endif /* MESSAGEBOX_HPP_ */
