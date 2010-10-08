#include <libwiisys.h>
#include <libwui.h>

class GraphicDisclaimer : public Libwui::Component::Form
{
  private:
	Libwui::Component::Button btnContinue;
	Libwui::Component::Button btnExit;
	Libwui::Component::TextAera textDisclaimer;


  public:
    GraphicDisclaimer() ;

  protected:
    void InitializeComponents();
    void Exit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
};
