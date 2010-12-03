#include <Libwui/Component/Label.hpp>
#include <libwui/FreeTypeGX.h>
#include <sstream>
#include <Libwui/Resources/FontResource.hpp>
#include <Libwui/Resources/FontResourceManager.hpp>
#include <Libwui/UIManager.hpp>
#include <Libwui/video.h>

using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys;

#define TEXT_SCROLL_DELAY   8
#define TEXT_SCROLL_INITIAL_DELAY 6

Label::Label(const string& text, int s, GXColor c, int margin)
    : txt(text),
    size(s),
    color(c),
    margin(margin),
    textScrollPos(0),
    scrollToRight(true),
    textScrollInitialDelay(TEXT_SCROLL_INITIAL_DELAY),
    textScrollDelay(TEXT_SCROLL_DELAY),
    style(FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE),
    useParentSize(true)
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
    ForeColor((GXColor)
              {
                r, g, b, a
              }
             );
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
  else if(tag == "SetFont")
    SetFont(params.str());
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
  if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "SetFont", font);
    UIManager::AddMessage(m);
    return;
  }

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

  if(size > MAX_FONT_SIZE)
    this->size = MAX_FONT_SIZE;
  else
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

  style &= ~(FTGX_JUSTIFY_LEFT | FTGX_JUSTIFY_RIGHT | FTGX_JUSTIFY_CENTER | FTGX_ALIGN_TOP | FTGX_ALIGN_BOTTOM | FTGX_ALIGN_MIDDLE);

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
  FontResource* resource = FontResourceManager::Get(_font);

  if(!resource->IsInitialized(size))
    resource->Initialize(size);

  //test si le text est trop long pour le label (et donc scroll)
  bool needScroll = (GetWidth() - (2.0 * margin)) < resource->Font()->getWidth(txt);


  string textToDisplay = txt;

  //recuperation du text reelle a afficher
  if(needScroll)
  {
    //maj des variable de scroll
    if(FrameTimer % textScrollDelay == 0)
    {
      //on attend le delai de d�part
      if(textScrollInitialDelay)
        textScrollInitialDelay--;
      else if(scrollToRight)
      {
        // une fois arriv� au bout, on inverse le sens du scroll
    	if(resource->Font()->getWidth(textToDisplay.substr(++textScrollPos)) <= (GetWidth() - (2.0 * margin)))
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
    u8 nbChar = textToDisplay.substr(textScrollPos).size();
    do{
    	nbChar--;
    }while(resource->Font()->getWidth(textToDisplay.substr(textScrollPos, nbChar)) > (GetWidth() - (2.0 * margin)));
	textToDisplay = textToDisplay.substr(textScrollPos, nbChar + 1);
  }

  //Get the real position
  s32 alignOffsetX = 0;
  s32 alignOffsetY = 0;

  switch(style & 0x7)
  {
    case FTGX_JUSTIFY_LEFT:
      alignOffsetX = margin;
      break;
    case FTGX_JUSTIFY_RIGHT:
      alignOffsetX = Parent()->GetWidth() - resource->Font()->getWidth(textToDisplay);
      break;
    case FTGX_JUSTIFY_CENTER:
      alignOffsetX = (Parent()->GetWidth() - resource->Font()->getWidth(textToDisplay)) / 2;
      break;
  }

  switch(style & 0x70)
  {
    case FTGX_ALIGN_TOP:
      break;
    case FTGX_ALIGN_BOTTOM:
      alignOffsetY = Parent()->GetHeight() - resource->Font()->getHeight(textToDisplay);
      break;
    case FTGX_ALIGN_MIDDLE:
      alignOffsetY = (Parent()->GetHeight() - resource->Font()->getHeight(textToDisplay)) / 2;
      break;
  }

  u16 displayStyle = style & ~(FTGX_JUSTIFY_LEFT | FTGX_JUSTIFY_RIGHT | FTGX_JUSTIFY_CENTER | FTGX_ALIGN_TOP | FTGX_ALIGN_BOTTOM | FTGX_ALIGN_MIDDLE);
  displayStyle |= FTGX_JUSTIFY_LEFT | FTGX_ALIGN_TOP;
  DrawText(*resource->Font(size), this->GetLeft() + alignOffsetX, this->GetTop() + alignOffsetY, textToDisplay, color, displayStyle);

}

std::string Label::Text()
{
  return txt;
}

s32 Label::FontSize()
{
  return size;
}

void Label::SetSize(s32 w, s32 h)
{
  useParentSize = false;
  Control::SetSize(w, h);
}

s32 Label::GetWidth()
{
  if(useParentSize)
	return Parent()->GetWidth() - _xoffset;
	
  return _width;
}

s32 Label::GetHeight()
{
  if(useParentSize)
	return Parent()->GetHeight() - _yoffset;
	
  return _height;
}

s32 Label::GetMargin()
{
	return margin;
}

void Label::SetMargin(s32 m)
{
	margin = m;
}

uint16_t Label::GetTextWidth(FreeTypeGX& font, const string& text)
{
	wchar_t* wtext = FreeTypeGX::charToWideChar(text.c_str());
	uint16_t retVal = font.getWidth(wtext);
	free(wtext);
	return retVal;
}

uint16_t Label::GetTextHeight(FreeTypeGX& font, const string& text)
{
	wchar_t* wtext = FreeTypeGX::charToWideChar(text.c_str());
	uint16_t retVal = font.getHeight(wtext);
	free(wtext);
	return retVal;
}


uint16_t Label::DrawText(FreeTypeGX& font, int16_t x, int16_t y, const string& text, GXColor color, uint16_t textStyling)
{
	wchar_t* wtext = FreeTypeGX::charToWideChar(text.c_str());
	uint16_t retVal = font.drawText(x, y, wtext, color, textStyling);
	free(wtext);
	return retVal;
}