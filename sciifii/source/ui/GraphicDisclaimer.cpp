#ifdef ANEPACOMPILER

#include "GraphicDisclaimer.h"
#include "../Config.h"

using namespace UI;
using namespace UI::Component;
using namespace UI::Events;
using namespace std;
using namespace fastdelegate;

GraphicDisclaimer::GraphicDisclaimer() 
  : textDisclaimer(" ", 12, (GXColor){255,255,255,255})
{}

void GraphicDisclaimer::InitializeComponents()
{
  BackgroundImage("sd:/sciifii/default/disclaimer.png");
  SetSize(640, 480);

  btnExit.DefaultImage("sd:/sciifii/default/exitbutton_normal.png");
  btnExit.OverImage("sd:/sciifii/default/exitbutton_over.png");
  btnExit.SetSize(44,44);
  btnExit.SetPosition(590,430);
  btnExit.Click += MakeDelegate(this, &GraphicDisclaimer::Exit);
  btnExit.InitializeComponents();

  textDisclaimer.Text(Config::DisclaimerText());
  textDisclaimer.SetFont("sd:/font.ttf");
  textDisclaimer.SetPosition(130,250);
  textDisclaimer.SetSize(390,150);
  textDisclaimer.ForeColor((GXColor){255,0,0,255});
  textDisclaimer.InitializeComponents();

  btnContinue.DefaultImage("sd:/sciifii/default/go_button.png");
  btnContinue.OverImage("sd:/sciifii/default/go_button_over.png");
  btnContinue.Text("Click here !");
  textDisclaimer.SetFont("sd:/font.ttf");
  btnContinue.SetSize(164,40);
  btnContinue.SetPosition(238,430);
  btnContinue.InitializeComponents();


  Form::InitializeComponents();
  AddChildren(&btnExit);
  AddChildren(&btnContinue);
  AddChildren(&textDisclaimer);
}

void GraphicDisclaimer::Exit(Object* sender, CursorEventArgs* args)
{
  Visible(false);
}

#endif
