#include <libwui/Component/ProgressBar.h>
#include <libwiisys/threading/ProgressEventArgs.h>
#include <libwui/Resources/Colors.h>
#include <libwui/UIManager.hpp>
#include <Libwui/video.h>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwiisys;
using namespace Libwiisys::Threading;

using namespace std;

ProgressBar::ProgressBar() :
	MaxValue(1),
	ActualValue(0), 
	l("", 12, Colors::Black()),
	usedColor(Colors::Green()),
	defaultColor(Colors::White())

{	}

void ProgressBar::InitializeComponents()
{
	l.SetTextAlignment(HAlign_Center, VAlign_Middle);
	AddChildren(&l);
	Control::InitializeComponents();
}

void ProgressBar::SetMaxValue(f32 max)
{
	if (InvokeRequired())
	{
		stringstream params;
		params << max;
		Message* m = new Message(_fullId, "MaxValue", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		if (max > 0)
			MaxValue = max;
	}
}

void ProgressBar::SetActualValue(f32 act)
{
	if (InvokeRequired())
	{
		stringstream params;
		params << act;
		Message* m = new Message(_fullId, "ActualValue", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		if (act > MaxValue) act = MaxValue;
		ActualValue = act;
	}
}

void ProgressBar::ProcessMessage(Message& message)
{
	if (message.GetComponentId() != _fullId)
	{
		Control::ProcessMessage(message);
		return;
	}

	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());

	if (tag == "MaxValue")
	{
		f32 m;
		params >> m;
		SetMaxValue(m);
	}
	else if (tag == "ActualValue")
	{
		f32 a;
		params >> a;
		SetActualValue(a);
	}
	else if (tag == "DefaultColor")
	{
		u8 r, g, b, a;
		params >> r >> g >> b >> a;
		SetDefaultColor(Colors::FromRGBA(r, g, b, a));
	}
	else if (tag == "UsedColor")
	{
		u8 r, g, b, a;
		params >> r >> g >> b >> a;
		SetUsedColor(Colors::FromRGBA(r, g, b, a));
	}
	else
		Control::ProcessMessage(message);
}

void ProgressBar::SetText(string s)
{
	l.Text(s);
}

void ProgressBar::SetValue(Object *sender, ProgressEventArgs *p)
{
	SetActualValue(p->percent);
	l.Text(p->message);
}

void ProgressBar::SetUsedColor(GXColor c)
{
	if (InvokeRequired())
	{
		stringstream params;
		params << c.r << " " << c.g << " " << c.b << " " << c.a;
		Message* m = new Message(_fullId, "UsedColor", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		usedColor = c;
	}
}

void ProgressBar::SetDefaultColor(GXColor c)
{
	if (InvokeRequired())
	{
		stringstream params;
		params << c.r << " " << c.g << " " << c.b << " " << c.a;
		Message* m = new Message(_fullId, "DefaultColor", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		defaultColor = c;
	}
}

void ProgressBar::Draw()
{
	Menu_DrawRectangle(GetLeft() + 1, GetTop() + 1, GetWidth() - 2, GetHeight()	- 2, defaultColor, 1);
	Menu_DrawRectangle(GetLeft() + 1, GetTop() + 1, (f32)(GetWidth() - 2) * (ActualValue / MaxValue), GetHeight() - 2,	usedColor, 1);
	Control::Draw();
}

void ProgressBar::ForeColor(GXColor c)
{
	l.ForeColor(c);
}

void ProgressBar::TextSize(int pt)
{
	l.FontSize(pt);
}

void ProgressBar::SetTextAlignement(HAlign halign, VAlign valign)
{
	l.HorizontalAlignement(halign);
	l.VerticalAlignement(valign);
}
