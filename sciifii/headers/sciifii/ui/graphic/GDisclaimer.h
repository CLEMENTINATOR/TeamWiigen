#include <libwiisys.h>
#include <libwui.h>

class GDisclaimer : public Libwui::Component::Form
{
  private:
	Libwui::Component::Button btnContinue;
	Libwui::Component::Button btnExit;
	Libwui::Component::TextAera textDisclaimer;


  public:
    GDisclaimer() ;

  protected:
    void InitializeComponents();
    void Exit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
};
