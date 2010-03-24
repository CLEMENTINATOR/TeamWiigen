#ifndef _UI_COMPONENT_BUTTON_H_
#define _UI_COMPONENT_BUTTON_H_

#include <string>
#include "../Control.hpp"
#include "Label.hpp"
namespace UI
{
	namespace Component
	{
		class Button : public UI::Control
		{			
		protected:			
			void OnClick(UI::Device::PadController &c);
			void OnCursorEnter();
			void OnCursorLeave();
			void OnCursorButtonDown(UI::Device::PadController &c);
			void OnCursorButtonUp(UI::Device::PadController &c);			
		public:
			Button();
			void InitializeComponents();
			void Draw();			
			virtual void ProcessMessage(Message& message);			
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
		private:
			std::string _currentImage;
			std::string _defaultImage;
			std::string _overImage;
			std::string _clickedImage;
			Label _lblText;
			
			void ChangeImage(const std::string _image);
		};
	}
}

#endif
