#include <Sciifii.h>

GExitMenuItem::GExitMenuItem(TiXmlElement* node)
: IMenuItem(node)
{
	Text(_text);
	SetSize(164,40);
	DefaultImage("sd:/sciifii/default/Exit_Default.png");
	OverImage("sd:/sciifii/default/Exit_Over.png");
	ClickedImage("sd:/sciifii/default/Exit_Clicked.png");
}

void GNavigationMenuItem::OnClick(Libwui::Device::PadController &c)
{
	NavigateEventArgs args;
	args.ValidateCurrentMenu = false;
	args.NavigateTo = "loader";
	args.MenuId = "";
	OnNavigate(args);
}