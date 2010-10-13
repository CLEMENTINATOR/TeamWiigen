#include <libwui.h>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace std;
using namespace fastdelegate;

void MessageBox::Show(Control* _current, std::string text, std::string title)
    {
    Control* parent = _current;
    _title.Text(title);
    _text.Text(text);
    if (parent == NULL) //non modal
	{
	return;
	}
    else
	{
	while (parent->Parent() != NULL)
	    {
	    parent = parent->Parent();
	    }

	}
    ImageResource* resource =
	    ImageResourceManager::Get(_boxImg.ImageLocation());
    SetSize(parent->GetWidth(), parent->GetHeight());
    SetPosition(0, 0);
    _boxImg.SetPosition((parent->GetWidth() / 2) - resource->Width() / 2,
	    (parent->GetHeight() / 2) - resource->Height() / 2);

    Visible(true);
    Enabled(true);
    UIManager::ShowDialog(*this);
    }
void MessageBox::UnShow(Object*sender, CursorEventArgs *c)
    {
    Visible(false);
    }
void MessageBox::Draw()
    {
    Control::Draw();
    }
MessageBox::MessageBox() :
    _title("", 12, Colors::FromRGBA(0, 0, 0, 255)), _text("", 12,
	    Colors::FromRGBA(0, 0, 0, 255))
    {
    BackgroundColor(Colors::FromRGBA(200, 200, 200, 175));
    _boxButton.Text("OK");
    _boxButton.Click += MakeDelegate(this, &MessageBox::UnShow);

    Visible(false);
    Enabled(false);

    }

void MessageBox::InitializeComponents()
    {

    AddChildren(&_boxImg);
    _boxImg.AddChildren(&_title);
    _boxImg.AddChildren(&_text);
    _boxImg.AddChildren(&_boxButton);
    Control::InitializeComponents();

    }

void MessageBox::SetTitlePosition(int x, int y)
    {
    _title.SetPosition(x, y);
    }
void MessageBox::SetTextPosition(int x, int y)
    {
    _text.SetPosition(x, y);
    }
void MessageBox::SetTitleSize(int x, int y)
    {
    _title.SetSize(x, y);
    }
void MessageBox::SetTextSize(int x, int y)
    {
    _text.SetSize(x, y);
    }

void MessageBox::SetMessageBoxImage(std::string s)
    {
    ImageResource* resource = ImageResourceManager::Get(s);
    _boxImg.ImageLocation(s);
    _boxImg.SetSize(resource->Width(), resource->Height());
    }
void MessageBox::DefaultButtonImage(std::string s)
    {
    ImageResource* resource = ImageResourceManager::Get(s);
    _boxButton.DefaultImage(s);
    _boxButton.SetSize(resource->Width(), resource->Height());
    _boxButton.DefaultImage(s);
    }
void MessageBox::OverButtonImage(std::string s)
    {
    _boxButton.OverImage(s);
    }
void MessageBox::ClickedButtonImage(std::string s)
    {
    _boxButton.ClickedImage(s);
    }
void MessageBox::SetButtonPosition(int x, int y)
    {
    _boxButton.SetPosition(x, y);
    }
