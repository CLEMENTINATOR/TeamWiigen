#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_
#include "../Control.hpp"
#include <libwiisys/threading/ProgressEventArgs.h>
#include "Label.hpp"
#include <string>

namespace Libwui
{
namespace Component
{
class ProgressBar: public Libwui::Control
{
public:
	ProgressBar();
	void SetText(std::string s);
	void InitializeComponents();
	void SetMaxValue(f32 max);
	void SetActualValue(f32 act);
	void SetValue(Libwiisys::Object *sender,Libwiisys::Threading::ProgressEventArgs *p);
	void ProcessMessage(Message& message);
	void SetUsedColor(GXColor c);
	void SetDefaultColor(GXColor c);
	void ForeColor(GXColor c);
	void TextSize(int pt);
	void SetTextAlignement(HAlign halign, VAlign valign);
private:
	f32 MaxValue;
	f32 ActualValue;
	Label l;
	GXColor usedColor;

	GXColor defaultColor;
protected:
	void Draw();
};
}
}
#endif /* PROGRESSBAR_H_ */
