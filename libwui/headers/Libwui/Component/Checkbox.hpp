#ifndef CHECKBOX_HPP_
#define CHECKBOX_HPP_

#include "../Control.hpp"
#include "Label.hpp"
#include <string>

namespace Libwui
{
namespace Component
{
class Checkbox: public Libwui::Control
{
protected:
	void OnClick(Libwui::Device::PadController &c);

public:
	Events::CursorEvent CheckChanged;
	void Draw();
	void OnCheckChanged(Libwui::Device::PadController &c);
	Checkbox();
	virtual ~Checkbox();
	void InitializeComponents();
	std::string DefaultImage() const;
	void DefaultImage(const std::string& imagePath);
	std::string CheckedImage() const;
	void CheckedImage(const std::string& imagePath);
	virtual void ProcessMessage(Message& message);
	void SetTextAlignement(HAlign halign, VAlign valign);
	HAlign TextHorizontalAlignement() const;
	VAlign TextVerticalAlignement() const;
	void Text(const std::string& text);
	void ForeColor(GXColor c);
	void TextSize(int pt);
	void CurrentAlign(const HAlign& align);

	bool Checked() const;
private:
	std::string _currentImage;
	std::string _checkedImage;
	std::string _defaultImage;
	Label _ckeckboxText;
	bool _checked;
	HAlign _currentAlign;

};

}
}

#endif /* CHECKBOX_HPP_ */
