#include "FileViewer.h"

FileViewer::FileViewer()
{
	BackgroundColor((GXColor){255,0,0,255});
}

FileView* FileViewer::SelectedItem() const
{
	return NULL;
}
