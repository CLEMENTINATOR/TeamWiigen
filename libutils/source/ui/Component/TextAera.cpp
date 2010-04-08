#include <ui/Component/TextAera.h>
#include <ui/UIManager.hpp>
#include <ui/video.h>

#include <sstream>

using namespace std;
using namespace UI;
using namespace UI::Component;

TextAera::TextAera(const string& text, int s, GXColor c)
: txt(text),
  size(s),
  color(c),
  _invalidated(true)
{}

TextAera::~TextAera()
{
  Invalidate();
}

void TextAera::Invalidate()
{
	if(_invalidated)
		return;
		
	for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
	{
		RemoveChildren(*ite);
		delete *ite;
	}
		
	_textItems.clear();
	
	_invalidated = true;
}

void TextAera::Text(const string& text)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "Text", text);
		UIManager::AddMessage(m);
		return;
	}
	
	txt = text;
	Invalidate();
}

void TextAera::SetFont(const std::string& font)
{
	if(InvokeRequired())
	{
	  Message* m = new Message(_fullId, "SetFont", font);
	  UIManager::AddMessage(m);
	  return;
	}
	
	_font = font;
	
	if(!_invalidated)
		for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
			(*ite)->SetFont(font);
}

void TextAera::FontSize(int size)
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
	
	if(!_invalidated)
		for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
			(*ite)->FontSize(size);
}

void TextAera::ForeColor(GXColor color)
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
	if(!_invalidated)
		for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
			(*ite)->ForeColor(color);
}

void TextAera::ProcessMessage(Message& message)
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
	else if(tag == "SetFont")
		SetFont(params.str());
	else
		Control::ProcessMessage(message);
}

void TextAera::SetSize(int w, int h)
{
	Invalidate();
	Control::SetSize(w, h);
}

void TextAera::Draw()
{
	EnsureItems();	
	Control::Draw();
}

void TextAera::EnsureItems()
{
  if(!_invalidated)
	return;
	
  u8 nbCharMax = (_width * 2.0) / size;
  
  char* buffer = new char[nbCharMax + 1];
  try
  {
    stringstream txtStream;
    txtStream << txt;
  
	while(!txtStream.eof())
	{
		if(((s32)(_textItems.size() + 1) * size) > _height)
			break;
			
		txtStream.getline(buffer, nbCharMax + 1);
		Label* lbl = new Label(buffer, size, color);
		lbl->SetPosition(0, _textItems.size() * size);
		_textItems.push_back(lbl);
		AddChildren(lbl);
	}
	
	delete[] buffer;
  }
  catch(...)
  {
    delete[] buffer;
  }
}