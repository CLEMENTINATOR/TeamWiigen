#include <libwiisys.h>

class GraphicDisclaimer : public UI::Component::Form
  {
  private:
    UI::Component::Button btnContinue;
    UI::Component::Button btnExit;
    UI::Component::Label textDisclaimer;


  public:
    GraphicDisclaimer() ;

  protected:
    void InitializeComponents();
    void Exit(Object* sender, UI::Events::CursorEventArgs* args);
  };
