#include <sciifii/ui/graphic/GMemoryViewer.h>
#include <sstream>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Events;
using namespace std;
using namespace Libwiisys;
using namespace fastdelegate;

static int usedMemory = 0;

GMemoryViewer::GMemoryViewer()
  : view("", 12, (GXColor){0,0,0,255}),
		diff("", 12, (GXColor){0,0,0,255})
{
	SetSize(164,120);
}

void GMemoryViewer::InitializeComponents()
{
	btnView.DefaultImage("go_button.png");
  btnView.OverImage("go_button_over.png");
	btnView.Text("Memory");
  btnView.SetSize(164, 40);
  btnView.SetPosition(0, 0);
  btnView.SetFont("DisclaimerButton.ttf");
  btnView.Click += MakeDelegate(this, &GMemoryViewer::DisplayMemory);
	
	view.SetSize(164,40);
	view.SetPosition(0,40);
	
	diff.SetSize(164,40);
	diff.SetPosition(0,80);
	
	AddChildren(&btnView);
	AddChildren(&view);
	AddChildren(&diff);
}

void GMemoryViewer::DisplayMemory(Object* sender, CursorEventArgs* args)
{
	struct mallinfo nfo = mallinfo();
	stringstream data;
	
	data << nfo.uordblks;
	view.Text(data.str());
	
	data.str("");
	
	data << nfo.uordblks - usedMemory;
	diff.Text(data.str());
	
	usedMemory = nfo.uordblks;
}