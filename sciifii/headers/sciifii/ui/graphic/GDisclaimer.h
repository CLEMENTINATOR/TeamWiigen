#include <Libwiisys/Object.h>
#include <Libwui/Component/Form.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/TextAera.h>
#include <Libwui/Component/DropDownList.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <Libwui/Component/ProgressBar.h>
#include <sciifii/Config.h>

class GDisclaimer : public Libwui::Component::Form
{
  private:
    Libwui::Component::Button btnContinue;
    Libwui::Component::Button btnExit;
    Libwui::Component::TextAera textDisclaimer;
    //Libwui::Component::DropDownList list;
    //Libwui::Component::MessageBox mb;
    Libwui::Component::ProgressBar pBar;
  public:
    GDisclaimer() ;

  protected:
    void InitializeComponents();
    void Exit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
    void Continue(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
};
