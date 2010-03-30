#include <ui/Component/Label.hpp>
#include <ui/video.h>
#include <ui/UIManager.hpp>
#include <ui/Resources/FontResourceManager.hpp>
#include <sstream>

using namespace UI::Component;
using namespace UI::Resources;
using namespace std;

#define TEXT_SCROLL_DELAY			8
#define	TEXT_SCROLL_INITIAL_DELAY	6

Label::Label(const string& text, int s, GXColor c)
: txt(text),
  size(s),
  color(c),
  textScrollPos(0),
  scrollToRight(true),
  textScrollInitialDelay(TEXT_SCROLL_INITIAL_DELAY),
  textScrollDelay(TEXT_SCROLL_DELAY),
  style(FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE)
{}

void Label::ProcessMessage(Message& message)
{
	if(message.GetComponentId() != _fullId)
	{
		Control::ProcessMessage(message);
		return;
	}
	
	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());
	
	if(tag == "Text")
		Text(params.str());
	else if(tag == "FontSize")
	{
		int s;
		params >> s;
		FontSize(s);
	}
	else if(tag == "ForeColor")
	{
		u8 r, g, b, a;
		params >> r >> g >> b >> a;
		ForeColor((GXColor){r, g, b, a});
	}
	else if(tag == "Style")
	{
		int s;
		params >> s;
		Style(s);
	}
	else if(tag == "SetTextAlignment")
	{
		int h, v;
		params >> h >> v;
		SetTextAlignment((HAlign)h, (VAlign)v);
	}
	else
		Control::ProcessMessage(message);
}

void Label::Text(const string& text)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "Text", text);
		UIManager::AddMessage(m);
		return;
	}
	
	txt = text;
}

void Label::SetFont(const std::string& font)
{
	_font = font;
}

void Label::FontSize(int size)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << size;
		Message* m = new Message(_fullId, "FontSize", buffer.str());
		UIManager::AddMessage(m);
		return;
	}
	
	this->size = size;
}

void Label::ForeColor(GXColor color)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << color.r << " " << color.g << " " << color.b << " " << color.a;
		Message* m = new Message(_fullId, "ForeColor", buffer.str());
		UIManager::AddMessage(m);
		return;
	}
	
	this->color = color;
}

void Label::Style(u16 s)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << s;
		Message* m = new Message(_fullId, "Style", buffer.str());
		UIManager::AddMessage(m);
		return;
	}
	
	this->style = s;
}

void Label::SetTextAlignment(HAlign hor, VAlign vert)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << (int)hor << " " << (int)vert;
		Message* m = new Message(_fullId, "SetTextAlignment", buffer.str());
		UIManager::AddMessage(m);
		return;
	}
	
	style &= ~hor & ~vert;

	switch(hor)
	{
		case HAlign_Left:
			style |= FTGX_JUSTIFY_LEFT;
			break;
		case HAlign_Right:
			style |= FTGX_JUSTIFY_RIGHT;
			break;
		default:
			style |= FTGX_JUSTIFY_CENTER;
			break;
	}
	switch(vert)
	{
		case VAlign_Top:
			style |= FTGX_ALIGN_TOP;
			break;
		case VAlign_Bottom:
			style |= FTGX_ALIGN_BOTTOM;
			break;
		default:
			style |= FTGX_ALIGN_MIDDLE;
			break;
	}
}

void Label::Draw()
{
	//majoration de la taille en pt
	int realSize = size;
	if(realSize > MAX_FONT_SIZE)
		realSize = MAX_FONT_SIZE;
		
	
	FontResource* resource = FontResourceManager::Get(_font);
	
	if(!resource->IsInitialized())
		resource->Initialize();
	
	resource->Font()->changeFontSize(realSize);

	
	//test si le text est trop long pour le label (et donc scroll)
	u8 nbCharMax = (_width * 2.0) / realSize;
	bool needScroll = nbCharMax < txt.length();
	
	//recupération du text réelle a afficher
	if(needScroll)
	{
		//maj des variable de scroll
		if(FrameTimer % textScrollDelay == 0)
		{
			//on attend le delai de départ
			if(textScrollInitialDelay)
				textScrollInitialDelay--;
			else if(scrollToRight)
			{
				// une fois arrivé au bout, on inverse le sens du scroll
				if((u32)(++textScrollPos + nbCharMax) == txt.length())
				{
					scrollToRight = !scrollToRight;
					textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
				}
			}
			//on part a gauche
			else if(--textScrollPos  == 0)
			{
				scrollToRight = !scrollToRight;
				textScrollInitialDelay = TEXT_SCROLL_INITIAL_DELAY;
			}
		}
		resource->Font()->drawText(this->GetLeft(), this->GetTop(), txt.substr(textScrollPos, nbCharMax), color, style);
	}
	else
		resource->Font()->drawText(this->GetLeft(), this->GetTop(), txt, color, style);
	
}
