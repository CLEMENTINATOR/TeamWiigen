#ifndef _UI_COMPONENT_BUTTON_H_
#define _UI_COMPONENT_BUTTON_H_

#include <string>
#include "../Control.hpp"
#include "Label.hpp"

namespace Libwui
{
  namespace Component
  {
    class Button : public Libwui::Control
    {
      protected:
        void OnClick(Libwui::Device::PadController &c);
        void OnCursorEnter();
        void OnCursorLeave();
        void OnCursorButtonDown(Libwui::Device::PadController &c);
        void OnCursorButtonUp(Libwui::Device::PadController &c);
      public:
        Button();
        ~Button();
        void InitializeComponents();
        void Draw();
        virtual void ProcessMessage(Message& message);
        virtual void ProcessTrigger(Libwui::Device::PadController& c, std::string rootElementId);
        std::string CurrentImage();
        void DefaultImage(const std::string& imagePath);
        std::string DefaultImage() const;
        void OverImage(const std::string& imagePath);
        std::string OverImage() const;
        void ClickedImage(const std::string& imagePath);
        std::string ClickedImage() const;
        void SetTextAlignement(HAlign halign, VAlign valign);
        HAlign TextHorizontalAlignement() const;
        VAlign TextVerticalAlignement() const;
        void Text(const std::string& text);
        void ForeColor(GXColor c);
        void TextSize(int pt);
        void SetFont(const std::string& font);
        void DefineTrigger(u32 flag);

      private:
        std::string _currentImage;
        std::string _defaultImage;
        std::string _overImage;
        std::string _clickedImage;
        Label _lblText;
        bool _triggerState;
    };
  }
}

#endif
