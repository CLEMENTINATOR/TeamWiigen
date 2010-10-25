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

	textDisclaimer.Text(Config::DisclaimerText());
	textDisclaimer.SetPosition(130, 190);
	textDisclaimer.SetSize(390, 150);
	textDisclaimer.FontSize(12);
	textDisclaimer.ForeColor((GXColor){255,0,0,255});

	btnContinue.DefaultImage("sd:/sciifii/default/go_button.png");
	btnContinue.OverImage("sd:/sciifii/default/go_button_over.png");
	btnContinue.Text("Click here !");
	btnContinue.SetSize(164, 40);
	btnContinue.SetPosition(238, 370);
	btnContinue.Click += MakeDelegate(this, &GDisclaimer::Continue);

	AddChildren(&btnExit);
	AddChildren(&btnContinue);
	AddChildren(&textDisclaimer);

	Form::InitializeComponents();
}

void GDisclaimer::Exit(Object* sender, CursorEventArgs* args)
{
	Visible(false);
	throw AbortException();
}

void GDisclaimer::Continue(Object* sender, CursorEventArgs* args)
{
	Visible(false);
}
