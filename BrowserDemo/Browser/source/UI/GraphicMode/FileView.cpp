#include "FileView.h"
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>

using namespace std;
using namespace UI;

FileView::FileView(const string& path, bool folder) : _folder(folder), _lblFileName("")
{
	Path(path);
}

void FileView::Path(const string& path)
{
	_path = path;
	_pathName = Path::GetFileName(path);
	std::string imagePath;
	if(!_folder)
	{
		imagePath = "sd:/apps/browser/images/" + Path::GetFileExtension(path);
		if(!File::Exists(imagePath))
			imagePath = "sd:/apps/browser/images/default_file.png";
	}
	else
		imagePath = "sd:/apps/browser/images/folder.png";
		
	_imgFile.ImageLocation(imagePath);
}

string FileView::Path() const
{
	return _path;
}

void FileView::InitializeComponents()
{
	SetSize(130,100);
	
	_imgFile.HorizontalAlignement(HAlign_Center);
	_imgFile.VerticalAlignement(VAlign_Top);
	_imgFile.SetSize(72,72);	
	_imgFile.SetPosition(10,10);
	
	_lblFileName.Text(_pathName.c_str());
	_lblFileName.HorizontalAlignement(HAlign_Center);
	_lblFileName.VerticalAlignement(VAlign_Bottom);
	_lblFileName.SetSize(110, 20);
	_lblFileName.SetPosition(10,-10);
	
	AddChildren(&_lblFileName);
	AddChildren(&_imgFile);
}
