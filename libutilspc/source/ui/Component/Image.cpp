#include <ui/Component/Image.hpp>
#include <ui/Resources/ImageResource.hpp>
#include <ui/Resources/ImageResourceManager.hpp>
#include <ui/UIManager.hpp>
#include <ui/video.h>
#include <sstream>

using namespace std;
using namespace UI::Component;
using namespace UI::Resources;

Image::Image()
: _mode(ResizeMode_FitToFill)
{}

void Image::ProcessMessage(Message& message)
{
	if(message.GetComponentId() != _fullId)
	{
		Control::ProcessMessage(message);
		return;
	}
	
	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());
	
	if(tag == "FillMode")
	{
		int mode;
		params >> mode;
		FillMode((ResizeMode)mode);
	}
	else if(tag == "ImageLocation")
		ImageLocation(params.str());
	else
		Control::ProcessMessage(message);
}

void Image::FillMode(ResizeMode mode)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << (int)mode;
		Message* m = new Message(_fullId, "FillMode", buffer.str());
		UIManager::AddMessage(m);
		return;
	}
	
	_mode = mode;
}

ResizeMode Image::FillMode() const
{
	return _mode;
}

void Image::ImageLocation(const std::string& location)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "ImageLocation", location);
		UIManager::AddMessage(m);
		return;
	}
	
	_imagePath = location;
}

std::string Image::ImageLocation() const
{
	return _imagePath;
}

void Image::Draw()
{
	if(_imagePath.length() == 0)
		return;
		
	ImageResource* resource = ImageResourceManager::Get(_imagePath);
	f32 xscale = 1;
	f32 yscale = 1;
	
	//find x and y ratios
	if(_mode != ResizeMode_None)
	{
		xscale = ((f32)GetWidth())/resource->Width();
		yscale = ((f32)GetHeight())/resource->Height();
	}
	
	if(_mode == ResizeMode_FitToFill)
	{
		if(xscale < yscale)
			yscale = xscale;
		else
			xscale = yscale;
	}
	
	Menu_DrawImg(GetLeft(), GetTop(), GetWidth(), GetHeight(), resource->Image(), 0, xscale, yscale, 255);
	Control::Draw();
}
