#ifndef CHECKBOX_HPP_
#define CHECKBOX_HPP_

#include "../Control.hpp"
#include "Label.hpp"
#include <string>

namespace Libwui
{
	namespace Component
	{
		class Checkbox: public Control
		{
		protected:
			void OnClick(Libwui::Device::PadController &c);
			virtual void OnCheckChanged(Libwui::Device::PadController &c);

			void EnsureItems();		
		public:
			Checkbox();
			void InitializeComponents();
			virtual void ProcessMessage(Message& message);
			
			std::string DefaultImage() const;
			void DefaultImage(const std::string& imagePath);
			
			std::string CheckedImage() const;
			void CheckedImage(const std::string& imagePath);
			
			bool Checked() const;
			void Checked(bool c);
			
			void Text(const std::string& text);
			void ForeColor(GXColor c);
			void FontSize(int pt);
			void TextPosition(const HAlign& align);

			Events::CursorEvent CheckChanged;
		private:
			std::string _currentImage;
			std::string _checkedImage;
			std::string _defaultImage;
			Label _checkBoxText;
			Image _checkBoxImg;
			bool _checked;
			HAlign _textPosition;
		};
	}
}

#endif /* CHECKBOX_HPP_ */
