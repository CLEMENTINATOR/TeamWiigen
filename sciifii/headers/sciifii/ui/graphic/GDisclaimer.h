#include <Libwiisys/Object.h>
#include <Libwui/Component/Form.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/TextAera.h>
#include <Libwui/Component/DropDownList.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <sciifii/Config.h>

class GDisclaimer : public Libwui::Component::Form
{
  private:
    Libwui::Component::Button btnContinue;
    Libwui::Component::Button btnExit;
    Libwui::Component::TextAera textDisclaimer;
    Libwui::Component::DropDownList list;
    Libwui::Component::MessageBox mb;
  public:
    GDisclaimer() ;

  protected:
    void InitializeComponents();
    void Exit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
    void PopupExit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
};
