#include <Sciifii.h>
#include <libwui.h>

using namespace Libwiisys;
using namespace Libwui::Component;
using namespace Libwui::Events;
using namespace std;
using namespace fastdelegate;

GDisclaimer::GDisclaimer()
  : textDisclaimer(" ", 12, (GXColor){255,255,255,255})
{}

void GDisclaimer::InitializeComponents()
{
  BackgroundImage("sd:/sciifii/default/disclaimer.png");
  SetSize(640, 480);

  btnExit.DefaultImage("sd:/sciifii/default/exitbutton_normal.png");
  btnExit.OverImage("sd:/sciifii/default/exitbutton_over.png");
  btnExit.SetSize(44,44);
  btnExit.SetPosition(545,415);
  btnExit.Click += MakeDelegate(this, &GDisclaimer::Exit);
  btnExit.InitializeComponents();


  checkBox.DefaultImage("sd:/sciifii/default/disable_button.png");
  checkBox.CheckedImage("sd:/sciifii/default/enable_button.png");
  checkBox.SetSize(24,24);
  checkBox.Text("Jeanmi  !");
 //checkBox.CurrentAlign(Libwui::HAlign_Left);
  checkBox.SetPosition(120,120);
  checkBox.InitializeComponents();


  textDisclaimer.Text(Config::DisclaimerText());
  textDisclaimer.SetPosition(130,250);
  textDisclaimer.SetSize(390,150);
  textDisclaimer.ForeColor((GXColor){255,0,0,255});
  textDisclaimer.InitializeComponents();

  btnContinue.DefaultImage("sd:/sciifii/default/go_button.png");
  btnContinue.OverImage("sd:/sciifii/default/go_button_over.png");
  btnContinue.Text("Click here !");
  btnContinue.SetSize(164,40);
  btnContinue.SetPosition(238,430);
  btnContinue.InitializeComponents();


  Form::InitializeComponents();
  AddChildren(&btnExit);
  AddChildren(&btnContinue);
  AddChildren(&textDisclaimer);
  AddChildren(&checkBox);
}

void GDisclaimer::Exit(Object* sender, CursorEventArgs* args)
{
  Visible(false);
}
