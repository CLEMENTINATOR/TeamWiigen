#include <libutils/fs/Path.h>
#include <libutils/fs/File.h>
#include <libutils/fs/Directory.h>
#include <libutils/Dol.h>
#include <libutils/Elf.h>
#include <libutils/fs/Device.h>
#include "DirectoryViewer.h"
#include "ActionMenu.h"
#include "ConfigMenu.h"
#include <wiiuse/wpad.h>
#include <iostream>
#include <FastDelegate.h>
#include "../../business/FileSystemManager.h"
#include "../../Memory.h"

using namespace std;
using namespace fastdelegate;

DirectoryViewer::DirectoryViewer()
	: MenuBase(),
	  currentElement(),
	  displayedDirectory(),
	  actionMenu(),
	  configMenu()
{}

void DirectoryViewer::Display(const std::vector<std::string> &directories,const std::vector<std::string> &files)
{
	//clear screen
	cout << "\x1b[2J";
	cout << "\x1b[2;0H";

	// nom de la team
	cout << "================================================" << endl
	     << "File Browser made by Arasium, Teton and Fanta" << endl
	     << "Thank to all the staff (beta testers and others)" << endl
	     << "================================================" << endl << endl;

	//legend
	cout << "A: enter in a folder" << endl
	     << "B: return to parent folder" << endl
	     << "+: open the file menu" << endl
	     << "HOME: Open the main menu" << endl  << endl;

	cout <<"Current directory: " << displayedDirectory << endl << endl;

	u32 position = 0;

	nbItems = directories.size() + files.size();
	if(nbItems > MAX_MENU_ITEM)
		skipMax = nbItems - MAX_MENU_ITEM;
	else
		skipMax = 0;

	for(vector<string>::const_iterator dir = directories.begin(); dir != directories.end(); dir++)
	{
		if(position < skip)
		{
			position++;
			continue;
		}
		else if (position >= skip + MAX_MENU_ITEM)
			return;

		string shortPath;

		 if(displayedDirectory=="") shortPath=*dir;
		 else  shortPath = Path::GetFileName(*dir);

		if(position - skip == cursorPosition)
		{
			cout << ">>> * ";
			currentElement = *dir;
		}
		else
			cout << "    * ";

		cout << shortPath << endl;

		position++;
	}

	for(vector<string>::const_iterator file = files.begin(); file != files.end(); file++)
	{
		if(position < skip)
		{
			position++;
			continue;
		}
		else if (position >= skip + MAX_MENU_ITEM)
			return;

		string shortPath = Path::GetFileName(*file);

		if(position - skip == cursorPosition)
		{
			cout << ">>>   ";
			currentElement = *file;
		}
		else
			cout << "      ";

		cout << shortPath << endl;

		position++;
	}

	// Wait for the next frame
	VIDEO_WaitVSync();
}

void DirectoryViewer::Show()
{
	vector<string> directories;
	vector<string> files;
	bool refreshElements = true;
	bool emptyFolder = false;

	while(true)
	{
		if(refreshElements)
		{
			directories = GetDirectories();
			files = GetFiles();
			if(files.size() + directories.size() == 0)
			{
				emptyFolder = true;
				files.push_back(displayedDirectory + "/Empty Directory");
			}
			else
				emptyFolder = false;

			refreshElements = false;
		}

		Display(directories, files);

		//DoAction on buttonpressed
		u32 command = GetCommand();

		if(command & WPAD_BUTTON_DOWN)
		{
			cursorPosition++;
			if(cursorPosition >= nbItems)
				cursorPosition = nbItems - 1;
			else if(cursorPosition >= MAX_MENU_ITEM)
			{
				cursorPosition = MAX_MENU_ITEM - 1;
				//decalage du menu
				if(skip < skipMax)
					skip++;
			}
		}
		else if(command & WPAD_BUTTON_UP)
		{
			cursorPosition--;
			//cursorPosition est unsigned donc < 0 impossible
			// a la place, cursorPosition = u32MAX
			if(cursorPosition == (u32)-1)
			{
				cursorPosition = 0;
				if(skip > 0)
					skip--;
			}
		}
		else if((command & WPAD_BUTTON_A) && !emptyFolder)
		{
			if(Directory::Exists(currentElement))
			{
				cursorPosition = 0;
				skip = 0;
				displayedDirectory = currentElement;
				refreshElements = true;
			}
			else if(File::Exists(currentElement))
				ExecuteFile();
		}
		else if(command & WPAD_BUTTON_B)
		{
			if(displayedDirectory != "")
			{
				cursorPosition = 0;
				skip = 0;
				//if is root
				if(displayedDirectory == Path::GetRoot(displayedDirectory))
					displayedDirectory = "";
				else
					displayedDirectory = Path::GetParentDirectory(displayedDirectory);
				refreshElements = true;
			}
		}
		else if((command & WPAD_BUTTON_PLUS) && !emptyFolder)
		{
			refreshElements = DoAction();
			if(refreshElements)
				cursorPosition = 0;
		}
		else if(command & WPAD_BUTTON_HOME)
			configMenu.Show();
	}
}

void DirectoryViewer::ExecuteFile()
{
	string extension = Path::GetFileExtension(currentElement);
	cout << endl << "Launching " << extension << " file. Please wait...." << endl;
	
	try
	{
		if(extension == "dol" || extension == "DOL")
		{
			WPAD_Flush(0);
			WPAD_Disconnect(0);
			WPAD_Shutdown();
			Dol::Execute(currentElement, (void*)EXECUTABLE_MEM_ADDR);
		}
		if(extension == "elf" || extension == "ELF")
		{
			WPAD_Flush(0);
			WPAD_Disconnect(0);
			WPAD_Shutdown();
			Elf::Execute(currentElement, (void*)EXECUTABLE_MEM_ADDR);
		}
	}
	catch(...)
	{
		WPAD_Init();
		throw;
	}
}



bool DirectoryViewer::DoAction()
{
	ActionMenuResult result = actionMenu.Show(currentElement);

	switch(result)
	{
		case amResult_Copy:
			FileSystemManager::Current().Copy(currentElement);
			break;

		case amResult_Cut:
			if(!FileSystemManager::Current().Cut(currentElement))
			{
				cout << "It is impossible to cut this element." << endl;
				cout << "Press a key to continue" << endl;
				GetCommand();
			}
			break;

		case amResult_Delete:
			if(!FileSystemManager::Current().Delete(currentElement))
			{
				cout << "It is impossible to delete this element." << endl;
				cout << "Press a key to continue" << endl;
				GetCommand();
			}
			return true;

		case amResult_Paste:
			FileSystemManager::Current().BeforeCopiing += MakeDelegate(this, &DirectoryViewer::ConfirmAction);
			if(!FileSystemManager::Current().Paste(currentElement))
			{
				cout << "It is impossible to past this cuted/copied element." << endl;
				cout << "Press a key to continue" << endl;
				GetCommand();
			}
			FileSystemManager::Current().BeforeCopiing -= MakeDelegate(this, &DirectoryViewer::ConfirmAction);
			return true;
		case amResult_Install:
			FileSystemManager::Current().InstallWad(currentElement);
			return false;
		case amResult_Uninstall:
			FileSystemManager::Current().UninstallWad(currentElement);
			return false;
		case amResult_Cancel:
		default:
			break;
	}

	return false;
}

vector<string> DirectoryViewer::GetDirectories()
{
	if(displayedDirectory == "")
		return Device::GetAvailableRoots();
	else
		return Directory::GetDirectories(displayedDirectory);
}

vector<string> DirectoryViewer::GetFiles()
{
	if(displayedDirectory == "")
		return vector<string>();
	else
		return Directory::GetFiles(displayedDirectory);
}

void DirectoryViewer::ConfirmAction(Object *sender, FileSystemManagerEventArgs* args)
{
	s32 cols, rows;

	/* Get console metrics */
	CON_GetMetrics(&cols, &rows);

	cout << "\r";
	/* Erase line */
	for (int cnt = 1; cnt < cols; cnt++)
	{
		cout << " ";
	}
	cout << "\r";

	cout << "Copying " << args->ProcessControl()->sourcePath << " to " << args->ProcessControl()->destPath;
}
