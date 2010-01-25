#ifndef FILEVIEWER_H_
#define FILEVIEWER_H_

#include <libutils/ui/Control.hpp>
#include "FileView.h"

class FileViewer : public UI::Control
{
private:
	FileView *_files[12];
	FileView *_selectedFile;

public:
	FileViewer();
	FileView* SelectedItem() const;
};

#endif
