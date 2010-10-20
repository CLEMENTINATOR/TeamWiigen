#include <sciifii/ui/graphic/GDisclaimer.h>
#include <Libwiisys/Exceptions/AbortException.h>

using namespace Libwiisys;
using namespace Libwui::Component;
using namespace Libwui::Events;
using namespace Libwiisys::Exceptions;
using namespace std;
using namespace fastdelegate;

GDisclaimer::GDisclaimer() :
	textDisclaimer(" ", 12, (GXColor)
	{	255,255,255,255})
{
}

void GDisclaimer::InitializeComponents()
{
	BackgroundImage("sd:/sciifii/default/disclaimer.png");
	SetSize(640, 480);

	btnExit.DefaultImage("sd:/sciifii/default/exitbutton_normal.png");
	btnExit.OverImage("sd:/sciifii/default/exitbutton_over.png");
	btnExit.SetSize(44, 44);
	btnExit.SetPosition(545, 415);
	btnExit.Click += MakeDelegate(this, &GDisclaimer::Exit);
	btnExit.InitializeComponents();

	textDisclaimer.Text(Config::DisclaimerText());
	textDisclaimer.SetPosition(130, 250);
	textDisclaimer.SetSize(390, 150);
	textDisclaimer.ForeColor((GXColor)
	{	255,0,0,255});
	textDisclaimer.InitializeComponents();

	btnContinue.DefaultImage("sd:/sciifii/default/go_button.png");
	btnContinue.OverImage("sd:/sciifii/default/go_button_over.png");
	btnContinue.Text("Click here !");
	btnContinue.SetSize(164, 40);
	btnContinue.SetPosition(238, 430);
	btnContinue.InitializeComponents();
	btnContinue.Click += MakeDelegate(this, &GDisclaimer::Continue);

	/*list.SetPosition(100, 100);
	 list.SetSize(100, 100);
	 list.AddItem(0, "a");
	 list.AddItem(0, "b");
	 list.AddItem(0, "c");
	 list.AddItem(0, "d");
	 list.AddItem(0, "e");
	 list.AddItem(0, "f", true);
	 list.AddItem(0, "g");
	 list.AddItem(0, "h");
	 list.DefaultImage("sd:/sciifii/default/go_button_drop_normal.png");
	 list.OverImage("sd:/sciifii/default/go_button_drop_over.png");

	 list.UpDefaultImage("sd:/sciifii/default/arrow_up.png");
	 list.DownDefaultImage("sd:/sciifii/default/arrow_down.png");
	 list.UpOverImage("sd:/sciifii/default/arrow_up_over.png");
	 list.DownOverImage("sd:/sciifii/default/arrow_down_over.png");
	 list.InitializeComponents();*/

	/*mb.SetTitlePosition(16, 2);
	 mb.SetTitleSize(279, 14);
	 mb.SetTextPosition(16, 64);
	 mb.SetTextSize(279, 45);
	 mb.SetButtonPosition(76, 137);
	 mb.DefaultButtonImage("sd:/sciifii/default/go_button.png");
	 mb.OverButtonImage("sd:/sciifii/default/go_button_over.png");
	 mb.SetMessageBoxImage("sd:/sciifii/default/error_popup_screen.png");*/

	pBar.SetSize(300, 20);
	pBar.SetPosition(300, 300);
	pBar.SetMaxValue(100);
	pBar.SetActualValue(50);
	pBar.SetText("Jeanmi!");
	pBar.InitializeComponents();

	Form::InitializeComponents();
	AddChildren(&pBar);
	AddChildren(&btnExit);
	//AddChildren(&list);
	AddChildren(&btnContinue);
	AddChildren(&textDisclaimer);

}

void GDisclaimer::Exit(Object* sender, CursorEventArgs* args)
{
	Visible(false);
}

void GDisclaimer::Continue(Object* sender, CursorEventArgs* args)
{
	Visible(false);
}
