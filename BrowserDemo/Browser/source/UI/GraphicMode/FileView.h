#ifndef _FILEVIEW_H_
#define _FILEVIEW_H_

#include <libutils/ui/Control.hpp>
#include <libutils/ui/Component/Label.hpp>
#include <libutils/ui/Component/Image.hpp>

class FileView : public UI::Control
{
private:
	bool _folder;
	std::string _path;
	std::string _pathName;
	UI::Component::Label _lblFileName;
	UI::Component::Image _imgFile;

protected:
	void InitializeComponents();

public:
	FileView(const std::string& path, bool _folder = false);
	void Path(const std::string& path);
	std::string Path() const;
};

#endif
