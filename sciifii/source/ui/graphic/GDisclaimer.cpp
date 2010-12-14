#include <sciifii/ui/graphic/GDisclaimer.h>
#include <sciifii/business/common/ExitSciifiiException.h>

using namespace Libwiisys;
using namespace Libwui::Component;
using namespace Libwui::Audio;
using namespace Libwui::Events;
using namespace Libwiisys::Exceptions;
using namespace std;
using namespace fastdelegate;

GDisclaimer::GDisclaimer() :
    textDisclaimer(" ", 12, (GXColor)
               {
                 255,255,255,255
               })
{}

void GDisclaimer::InitializeComponents()
{
  BackgroundImage("disclaimer.png");
  SetSize(640, 480);

  btnExit.DefaultImage("exitbutton_normal.png");
  btnExit.OverImage("exitbutton_over.png");
  btnExit.SetSize(44, 44);
  btnExit.SetPosition(545, 415);
  btnExit.DefineTrigger(WPAD_BUTTON_HOME);
  btnExit.Click += MakeDelegate(this, &GDisclaimer::Exit);

  textDisclaimer.Text(Config::DisclaimerText());
  textDisclaimer.SetPosition(130, 250);
  textDisclaimer.SetSize(370, 110);
  textDisclaimer.FontSize(12);
  textDisclaimer.ForeColor((GXColor)
                           {
                             255,0,0,255
                           }
                          );
  textDisclaimer.SetFont("Disclaimer.ttf");

  btnContinue.DefaultImage("go_button.png");
  btnContinue.OverImage("go_button_over.png");
  btnContinue.Text("Click here !");
  btnContinue.SetSize(164, 40);
  btnContinue.SetPosition(238, 370);
  btnContinue.SetFont("DisclaimerButton.ttf");
  btnContinue.Click += MakeDelegate(this, &GDisclaimer::Continue);

  _themeDdl.SetPosition(420, 5);
  _themeDdl.SetSize(80, 80);

  player.SetPosition(10,400);
  player.SetTracklistFolder("sd:/mp3/");

  AddChildren(&btnExit);
  AddChildren(&btnContinue);
  AddChildren(&textDisclaimer);
  AddChildren(&_themeDdl);
  AddChildren(&player);
  Form::InitializeComponents();

  //AudioPlayer::GetAndReset().Play("sd:/test.mp3");
}

void GDisclaimer::Exit(Object* sender, CursorEventArgs* args)
{
  //AudioPlayer::GetAndReset();
  Visible(false);
  throw ExitSciifiiException();
}

void GDisclaimer::Continue(Object* sender, CursorEventArgs* args)
{
  //AudioPlayer::GetAndReset();
  Visible(false);
}
