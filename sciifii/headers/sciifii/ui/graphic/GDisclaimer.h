#include <Libwiisys/Object.h>
#include <Libwui/Component/Form.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/TextAera.h>
#include <Libwui/Component/DropDownList.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <Libwui/Component/ProgressBar.h>
#include <sciifii/ui/graphic/GThemeDdl.h>
#include <sciifii/Config.h>
#include <sciifii/ui/graphic/GAudioPlayer.h>

class GDisclaimer : public Libwui::Component::Form
{
  private:
    Libwui::Component::Button btnContinue;
    Libwui::Component::Button btnExit;
    Libwui::Component::TextAera textDisclaimer;
    GThemeDdl _themeDdl;
    GAudioPlayer player;
	
  public:
    GDisclaimer() ;

  protected:
    void InitializeComponents();
    void Exit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
    void Continue(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
};
