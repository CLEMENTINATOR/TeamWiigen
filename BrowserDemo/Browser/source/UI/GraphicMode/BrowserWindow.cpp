#include "BrowserWindow.h"

using namespace UI;
using namespace UI::Component;
using namespace UI::Events;
using namespace std;
using namespace fastdelegate;

void BrowserWindow::InitializeComponents()
{
	BackgroundImage("sd:/apps/browser/themes/default/background.png");
	SetSize(640, 480);

	btnExit.DefaultImage("sd:/apps/browser/themes/default/btnExit.png");
	//btnExit.OverImage("sd:/apps/browser/themes/default/btnExitOver.png");
	//btnExit.ClickedImage("sd:/apps/browser/themes/default/btnExitClick.png");
	btnExit.SetSize(56, 52);
	btnExit.SetPosition(550, 10);

	btnParentFolder.DefaultImage("sd:/apps/browser/themes/default/btnParent.png");
	//btnParentFolder.OverImage("sd:/apps/browser/themes/default/btnParentOver.png");
	//btnParentFolder.ClickedImage("sd:/apps/browser/themes/default/btnParentClick.png");
	btnParentFolder.SetSize(48, 52);
	btnParentFolder.SetPosition(30, 10);

	btnCopy.DefaultImage("sd:/apps/browser/themes/default/btnCopy.png");
	//btnCopy.OverImage("sd:/apps/browser/themes/default/btnCopyOver.png");
	//btnCopy.ClickedImage("sd:/apps/browser/themes/default/btnCopyClick.png");
	btnCopy.SetSize(84, 84);
	btnCopy.SetPosition(30, 65);

	btnCut.DefaultImage("sd:/apps/browser/themes/default/btnCut.png");
	//btnCut.OverImage("sd:/apps/browser/themes/default/btnCutOver.png");
	//btnCut.ClickedImage("sd:/apps/browser/themes/default/btnCutClick.png");
	btnCut.SetSize(96, 84);
	btnCut.SetPosition(2, 152);
	btnCut.InitializeComponents();

	btnPaste.DefaultImage("sd:/apps/browser/themes/default/btnPaste.png");
	//btnPaste.OverImage("sd:/apps/browser/themes/default/btnPasteOver.png");
	//btnPaste.ClickedImage("sd:/apps/browser/themes/default/btnPasteClick.png");
	btnPaste.SetSize(72, 76);
	btnPaste.SetPosition(26, 236);
	btnPaste.InitializeComponents();

	btnDelete.DefaultImage("sd:/apps/browser/themes/default/btnDelete.png");
	//btnDelete.OverImage("sd:/apps/browser/themes/default/btnDeleteOver.png");
	//btnDelete.ClickedImage("sd:/apps/browser/themes/default/btnDeleteClick.png");
	btnDelete.SetSize(64, 80);
	btnDelete.SetPosition(34, 315);
	btnDelete.InitializeComponents();

	viewer.SetPosition(100, 50);
	viewer.SetSize(540,430);

	btnRename.DefaultImage("sd:/apps/browser/themes/default/btnRename.png");
	//btnRename.OverImage("sd:/apps/browser/themes/default/btnRenameOver.png");
	//btnRename.ClickedImage("sd:/apps/browser/themes/default/btnRenameClick.png");
	btnRename.SetSize(112, 80);
	btnRename.SetPosition(7, 398);
	btnRename.InitializeComponents();

	lblAPropos.Text("By Arasium, Fanta, Teton");
	lblAPropos.HorizontalAlignement(HAlign_Right);
	lblAPropos.VerticalAlignement(VAlign_Bottom);
	lblAPropos.InitializeComponents();

	btnExit.Click += MakeDelegate(this, &BrowserWindow::Exit);

	Form::InitializeComponents();

	AddChildren(&btnExit);
	AddChildren(&btnParentFolder);
	AddChildren(&btnCopy);
	AddChildren(&btnCut);
	AddChildren(&btnPaste);
	AddChildren(&btnDelete);
	AddChildren(&btnRename);
	AddChildren(&lblAPropos);
	AddChildren(&viewer);
}

void BrowserWindow::Exit(Object* sender, CursorEventArgs* args)
{
	Visible(false);
}

