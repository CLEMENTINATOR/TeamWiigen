#include <libutils/ui/Component/Form.hpp>
#include <libutils/ui/Component/Button.hpp>
#include "FileViewer.h"

class BrowserWindow : public UI::Component::Form
{
private:
	UI::Component::Button btnExit;
	UI::Component::Button btnParentFolder;
	UI::Component::Button btnCopy;
	UI::Component::Button btnCut;
	UI::Component::Button btnPaste;
	UI::Component::Button btnDelete;
	UI::Component::Button btnRename;
	UI::Component::Label lblAPropos;

public:
	BrowserWindow(): lblAPropos("", 12, (GXColor){255,255,255,255}){}
	FileViewer viewer;

protected:
	void InitializeComponents();
	void Exit(Object* sender, UI::Events::CursorEventArgs* args);
};
