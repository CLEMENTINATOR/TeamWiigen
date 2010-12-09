#ifndef _TEXT_AERA_H_
#define _TEXT_AERA_H_

#include "../Control.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Image.hpp"

namespace Libwui
{
  namespace Component
  {
    class TextAera : public Control
    {
      public:
        TextAera(const std::string& text, int s = 12, GXColor c = (GXColor)
                 {
                   255, 255, 255, 255
                 }
                );
        virtual ~TextAera();

        void InitializeComponents();

        virtual void ProcessMessage(Message& message);

        virtual void SetSize(int w, int h);

        void Text(const std::string& text);
        void SetFont(const std::string& font);
        void FontSize(int size);
        void ForeColor(GXColor c);

      protected:
        std::string txt;
        std::string _font;
        int size; //!< Font size
        GXColor color; //!< Font color

        void Invalidate();
        void EnsureItems();

      private:
        std::vector<Label*> _textItems;
        Libwui::Component::Button _btnUp;
        Libwui::Component::Button _btnDown;
        Libwui::Component::Image _scrollBar;
        Libwui::Component::Image _scrollBall;
        bool _textChanged;
        bool _scrollChanged;
        bool _scrollBallMoved;
        int _nbSkip;
        bool _scrollBallDrag;

        void btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
        void btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
        void scrollBall_move(Object* sender, Libwui::Events::CursorEventArgs* args);
        void scollBall_held(Object* sender, Libwui::Events::CursorEventArgs* args);
        void scrollBall_release(Object* sender, Libwui::Events::CursorEventArgs* args);
        void scrollBall_leave(Object* sender, Libwiisys::EventArgs* args);
    };
  }
}
#endif
