#include <Libwui/Component/TextAera.h>
#include <Libwui/UIManager.hpp>
#include <Libwui/Resources/FontResource.hpp>
#include <Libwui/Resources/FontResourceManager.hpp>
#include <Libwiisys/String/UtilString.h>
#include <FastDelegate.h>
#include <math.h>
#include <sstream>
#include <iostream>

using namespace std;
using namespace fastdelegate;
using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwiisys::String;

TextAera::TextAera(const string& text, int s, GXColor c)
    : txt(text),
    size(s),
    color(c),
    _textChanged(true),
    _scrollChanged(true),
    _scrollBallMoved(false),
    _nbSkip(0),
    _scrollBallDrag(false)
{
	_btnUp.Click += MakeDelegate(this, &TextAera::btnUp_Clicked);
	_btnDown.Click += MakeDelegate(this, &TextAera::btnDown_Clicked);
	_scrollBall.CursorMove += MakeDelegate(this, &TextAera::scrollBall_move);
	_scrollBall.CursorButtonDown += MakeDelegate(this, &TextAera::scollBall_held);
	_scrollBall.CursorButtonUp += MakeDelegate(this, &TextAera::scrollBall_release);
}

TextAera::~TextAera()
{
  Invalidate();
}

void TextAera::InitializeComponents()
{
	_btnUp.SetSize(44, 44);
	_btnUp.SetPosition(GetWidth() - 33, -10);
	//_btnUp.HorizontalAlignement(HAlign_Right);
	//_btnUp.VerticalAlignement(VAlign_Top);
	_btnUp.Visible(false);
	_btnUp.Enabled(false);
	_btnUp.DefaultImage("arrow_up.png");
	_btnUp.OverImage("arrow_up_over.png");
	_btnUp.ClickedImage("arrow_up.png");
	AddChildren(&_btnUp);

	_btnDown.SetSize(44, 44);
	_btnDown.SetPosition(GetWidth() - 33, GetHeight() - 34);
	//_btnUp.HorizontalAlignement(HAlign_Right);
	//_btnUp.VerticalAlignement(VAlign_Bottom);
	_btnDown.Visible(false);
	_btnDown.Enabled(false);
	_btnDown.DefaultImage("arrow_Down.png");
	_btnDown.OverImage("arrow_Down_over.png");
	_btnDown.ClickedImage("arrow_Down.png");
	AddChildren(&_btnDown);

	_scrollBar.SetSize(44, GetHeight() - 10);
	_scrollBar.SetPosition(GetWidth() - 33, 5);
	_scrollBar.FillMode(ResizeMode_Fill);
	_scrollBar.VerticalAlignement(VAlign_Top);
	_scrollBar.Visible(false);
	_scrollBar.ImageLocation("scrollbar.png");
	AddChildren(&_scrollBar);

	_scrollBall.SetSize(44, 44);
	_scrollBall.SetPosition(0, 0);
	_scrollBall.Visible(false);
	_scrollBall.ImageLocation("scrollball.png");
	_scrollBar.AddChildren(&_scrollBall);

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
  _textChanged = true;
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
  _textChanged = true;
  Invalidate();
  /*if(!_invalidated)
    for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
      (*ite)->SetFont(font);*/
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

  _textChanged = true;
  Invalidate();
  /*if(!_invalidated)
    for(vector<Label*>::iterator ite = _textItems.begin(); ite != _textItems.end(); ite++)
      (*ite)->FontSize(size);*/
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
  _textChanged = true;
}

void TextAera::EnsureItems()
{
	if(_textChanged)
	{
		_scrollChanged = true;
		_btnUp.Visible(true);
		_btnDown.Visible(true);
		_scrollBar.Visible(true);
		_scrollBall.Visible(true);
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
			_scrollChanged = false;
			_btnUp.Visible(false);
			_btnDown.Visible(false);
			_scrollBar.Visible(false);
			_scrollBall.Visible(false);
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
	}
	if(_scrollChanged)
	{
		for(vector<Label*>::iterator it = _textItems.begin(); it != _textItems.end(); it++)
		{
			(*it)->Visible(false);
		}
		int nbToDisplay = floor((GetHeight() + 6) / (size + 6));
		if(_scrollBallMoved)
		{
			_nbSkip = floor((_scrollBall.GetTop() - _scrollBar.GetTop()) / ((_scrollBar.GetHeight() - 44) / (_textItems.size() - nbToDisplay)));
		}
		int j = 0;
		for(int i = _nbSkip; i < _nbSkip + nbToDisplay; i++)
		{
			_textItems[i]->Visible(true);
			_textItems[i]->SetPosition(0, j * (size + 6));
			j++;
		}
		if(_nbSkip == 0)
		{
			_btnUp.Enabled(false);
			_btnDown.Enabled(true);
		}
		else if(_nbSkip + nbToDisplay == _textItems.size())
		{
			_btnUp.Enabled(true);
			_btnDown.Enabled(false);
		}
		else
		{
			_btnUp.Enabled(true);
			_btnDown.Enabled(true);
		}
		if(!_scrollBallMoved)
			_scrollBall.SetPosition(0, floor(_nbSkip * ((_scrollBar.GetHeight() - 44) / (_textItems.size() - nbToDisplay))));
		_scrollChanged = false;
		_scrollBallMoved = false;
	}
}

void TextAera::btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_nbSkip++;
	_btnUp.Enabled(true);
	_btnDown.Enabled(false);
	_scrollChanged = true;
	Invalidate();
}

void TextAera::btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_nbSkip--;
	_btnUp.Enabled(_nbSkip != 0);
	_btnDown.Enabled(false);
	_scrollChanged = true;
	Invalidate();
}

void TextAera::scollBall_held(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_scrollBallDrag = true;
}

void TextAera::scrollBall_release(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_scrollBallDrag = false;
}

void TextAera::scrollBall_move(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	Device::PadController controller = args->Controller();
	if(controller.wpad.btns_h == 0)
	{
		_scrollBallDrag = false;
	}
	if(_scrollBallDrag)
	{
		if(controller.wpad.ir.valid && controller.wpad.ir.y >= _scrollBar.GetTop() + 22 && controller.wpad.ir.y <= _scrollBar.GetTop() + _scrollBar.GetHeight() - 22)
		{
			_scrollBall.SetPosition(0, (int)controller.wpad.ir.y - _scrollBar.GetTop() - 22);
			_scrollChanged = true;
			_scrollBallMoved = true;
			Invalidate();
		}
	}
}
