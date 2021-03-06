#ifndef _UI_COMPONENT_LABEL_H_
#define _UI_COMPONENT_LABEL_H_

#include "../Control.hpp"
#include <string>

#define MAX_FONT_SIZE 100

namespace Libwui
{
  namespace Component
  {
    class Label : public Control
    {
      public:
        Label(const std::string& text, s32 pixelSize = 12, GXColor c = (GXColor)
              {
                255, 255, 255, 255
              }
              , s32 margin = 0);

        virtual void ProcessMessage(Message& message);

        void Text(const std::string& text);
        void SetFont(const std::string& font);
        void FontSize(s32 size);
        void ForeColor(GXColor c);
        void Style(u16 s);

        virtual void HorizontalAlignement(HAlign alignement);
        HAlign HorizontalAlignement() const;
        virtual void VerticalAlignement(VAlign alignement);
        VAlign VerticalAlignement() const;
        void SetTextAlignment(HAlign hor, VAlign vert);

        void Draw();
        std::string Text();
        s32 FontSize();
        s32 GetMargin();
        void SetMargin(s32 m);

        virtual void SetSize(s32 w, s32 h);
        virtual s32 GetWidth();
        virtual s32 GetHeight();

      protected:
        std::string txt;
        std::string _font;
        s32 size; //!< Font size
        GXColor color; //!< Font color
        s32 margin;
        s32 textScrollPos; //!< Current starting index of text string for scrolling
        bool scrollToRight;
        s32 textScrollInitialDelay; //!< Delay to wait before starting to scroll
        s32 textScrollDelay; //!< Scrolling speed
        u16 style; //!< FreeTypeGX style attributes
        bool useParentSize;
    };
  }
}

#endif
