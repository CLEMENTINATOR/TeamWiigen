#include <Libwui/Component/TextAera.h>
#include <Libwui/UIManager.hpp>
#include <Libwui/Resources/FontResource.hpp>
#include <Libwui/Resources/FontResourceManager.hpp>
#include <Libwiisys/String/UtilString.h>
#include <FastDelegate.h>
#include <math.h>
#include <sstream>
#include <Libwui/Resources/ImageResource.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>

using namespace std;
using namespace fastdelegate;
using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace Libwiisys::String;

TextAera::TextAera(const string& text, int s, GXColor c)
    : txt(text),
    size(s),
    color(c),
    _nbToDisplay(0)
{
	_trackBar.ValueChanged += MakeDelegate(this, &TextAera::ScrollChanged);
}

TextAera::~TextAera()
{
  Invalidate();
}

void TextAera::InitializeComponents()
{
	ImageResource* resourceBar = ImageResourceManager::Get(_trackBar.ScrollBarImage());
	_trackBar.SetSize(resourceBar->Width(), GetHeight());
	_trackBar.SetPosition(GetWidth() - resourceBar->Width(), 0);
	_trackBar.SetMinValue(0);
	AddChildren(&_trackBar);

	Control::InitializeComponents();
}

void TextAera::Invalidate()
{
  for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
  {
    RemoveChildren(*ite);
    delete *ite;
  }

  _textItems.clear();
  Control::Invalidate();
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
  Invalidate();
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

  Invalidate();
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
    ForeColor((GXColor)
              {
                r, g, b, a
              }
             );
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

void TextAera::EnsureItems()
{
	_trackBar.Visible(true);
	FontResource* resource = FontResourceManager::Get(_font);
	if(!resource->IsInitialized(size))
	{
		resource->Initialize(size);
	}

	vector<string> lineList = UtilString::Split(txt, '\n');
	for(vector<string>::iterator lineIt = lineList.begin(); lineIt != lineList.end(); lineIt++)
	{
		if(GetWidth() - 44 < resource->Font(size)->getWidth(*lineIt))
		{
			string labelText;
			vector<string> wordList = UtilString::Split(*lineIt, ' ');
			do{
				int nbWord = wordList.size();
				do{
					labelText = "";
					for(int i = 0; i < nbWord; i++)
					{
						labelText += wordList[i] + " ";
					}
					nbWord--;
				}while(GetWidth() - 44 < resource->Font(size)->getWidth(labelText));
				Label* lbl = new Label(labelText, size, color);
				lbl->SetPosition(0, _textItems.size() * (size + 6));
				lbl->SetSize(GetWidth(), size);
				lbl->SetFont(_font);
				_textItems.push_back(lbl);
				AddChildren(lbl);
				wordList.erase(wordList.begin(), wordList.begin() + nbWord + 1);
			}while(!wordList.empty());
		}
		else
		{
			Label* lbl = new Label(*lineIt, size, color);
			lbl->SetPosition(0, _textItems.size() * (size + 6));
			lbl->SetSize(GetWidth(), size);
			lbl->SetFont(_font);
			_textItems.push_back(lbl);
			AddChildren(lbl);
		}
	}
	if(_textItems.back()->GetTop() + size <= GetHeight() + GetTop())
	{
		_trackBar.Visible(false);
		for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
		{
			RemoveChildren(*ite);
			delete *ite;
		}
		_textItems.clear();
		_textItems.push_back(new Label("coucou", size, color));
		for(vector<string>::iterator lineIt = lineList.begin(); lineIt != lineList.end(); lineIt++)
		{
			if(GetWidth() < resource->Font(size)->getWidth(*lineIt))
			{
				string labelText;
				vector<string> wordList = UtilString::Split(*lineIt, ' ');
				do{
					int nbWord = wordList.size();
					do{
						labelText = "";
						for(int i = 0; i < nbWord; i++)
						{
							labelText += wordList[i] + " ";
						}
						nbWord--;
					}while(GetWidth() < resource->Font(size)->getWidth(labelText));
					Label* lbl = new Label(labelText, size, color);
					lbl->SetPosition(0, _textItems.size() * (size + 6));
					lbl->SetSize(GetWidth(), size);
					lbl->SetFont(_font);
					_textItems.push_back(lbl);
					AddChildren(lbl);
					wordList.erase(wordList.begin(), wordList.begin() + nbWord + 1);
				}while(!wordList.empty());
			}
			else
			{
				Label* lbl = new Label(*lineIt, size, color);
				lbl->SetPosition(0, _textItems.size() * (size + 6));
				lbl->SetSize(GetWidth(), size);
				lbl->SetFont(_font);
				_textItems.push_back(lbl);
				AddChildren(lbl);
			}
		}
	}
	_nbToDisplay = floor((GetHeight() + 6) / (size + 6));
	_trackBar.SetValue(0);
	_trackBar.SetMaxValue(_textItems.size() - _nbToDisplay);
}

void TextAera::ScrollChanged(Object* sender, TrackBarEventArgs* args)
{
	for(vector<Label*>::iterator it = _textItems.begin(); it != _textItems.end(); it++)
	{
		(*it)->Visible(false);
	}
	u32 j = 0;
	for(u32 i = args->Value(); i < args->Value() + _nbToDisplay; i++)
	{
		_textItems[i]->Visible(true);
		_textItems[i]->SetPosition(0, j * (size + 6));
		j++;
	}
}

void TextAera::UpDefaultImage(const std::string& imagePath)
{
	_trackBar.UpDefaultImage(imagePath);
}

std::string TextAera::UpDefaultImage() const
{
	return _trackBar.UpDefaultImage();
}

void TextAera::UpOverImage(const std::string& imagePath)
{
	_trackBar.UpOverImage(imagePath);
}

std::string TextAera::UpOverImage() const
{
	return _trackBar.UpOverImage();
}

void TextAera::UpClickedImage(const std::string& imagePath)
{
	_trackBar.UpClickedImage(imagePath);
}

std::string TextAera::UpClickedImage() const
{
	return _trackBar.UpClickedImage();
}

void TextAera::DownDefaultImage(const std::string& imagePath)
{
	_trackBar.DownDefaultImage(imagePath);
}

std::string TextAera::DownDefaultImage() const
{
	return _trackBar.DownDefaultImage();
}

void TextAera::DownOverImage(const std::string& imagePath)
{
	_trackBar.DownOverImage(imagePath);
}

std::string TextAera::DownOverImage() const
{
	return _trackBar.DownOverImage();
}

void TextAera::DownClickedImage(const std::string& imagePath)
{
	_trackBar.DownClickedImage(imagePath);
}

std::string TextAera::DownClickedImage() const
{
	return _trackBar.DownClickedImage();
}

void TextAera::ScrollBarImage(const std::string& imagePath)
{
	_trackBar.ScrollBarImage(imagePath);
}

std::string TextAera::ScrollBarImage() const
{
	return _trackBar.ScrollBarImage();
}

void TextAera::ScrollBallImage(const std::string& imagePath)
{
	_trackBar.ScrollBallImage(imagePath);
}

std::string TextAera::ScrollBallImage() const
{
	return _trackBar.ScrollBallImage();
}
