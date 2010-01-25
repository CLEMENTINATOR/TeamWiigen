#include <iostream>
#include <wiiuse/wpad.h>
#include "ActionMenu.h"
#include "../../business/ConfigurationManager.h"
#include "../../business/FileSystemManager.h"
#include <libutils/fs/Path.h>
using namespace std;

ActionMenu::ActionMenu()
        : MenuBase(),
        selectIndex(0)
{
    actions.push_back("Copy");
    actions.push_back("Cut");
    actions.push_back("Paste");
    actions.push_back("Delete");
    actions.push_back("Install");
    actions.push_back("Uninstall");
    actions.push_back("Cancel");
}

void ActionMenu::Display()
{
    //clear screen
    cout << "\x1b[2J";
    cout << "\x1b[2;0H";

    u32 position = 0;

	// nom de la team
	cout << "================================================" << endl
	     << "File Browser made by Arasium, Teton and Fanta" << endl
	     << "Thank to all the staff (beta testers and others)" << endl
	     << "================================================" << endl << endl;

    //legend
    cout << "Choose what to do with the file:" << endl
    << _filePath << endl << endl;

    cout << "A: Execute the selected item" << endl
    << "B: Move the cursor to the exit menu item" << endl << endl;

    u32 displayIndex = 0;

    for (vector<string>::iterator ite = actions.begin(); ite != actions.end(); ite ++)
    {
	if (position == 0 && !FileSystemManager::Current().CanCopy(_filePath))
        {
            position++;
            continue;
        }
        if (position == 1 && !FileSystemManager::Current().CanCut(_filePath))
        {
            position++;
            continue;
        }
        if (position == 2 && !FileSystemManager::Current().CanPaste(_filePath))
        {
            position++;
            continue;
        }
        if (position == 3 && !FileSystemManager::Current().CanDelete(_filePath))
        {
            position++;
            continue;
        }
        if((position == 4 || position == 5) && Path::GetFileExtension(_filePath) != "wad")
        {
        	position++;
        	continue;
        }

        //Si on est sur la ligne a selectionner, alors on enregistre le vrai élement
        if (displayIndex == cursorPosition)
            selectIndex = position;

        cout << (displayIndex == cursorPosition ? ">>>   " : "      ") << *ite << endl;
        displayIndex++;
        position++;
    }

    nbItems = displayIndex;

    // Wait for the next frame
    VIDEO_WaitVSync();
}

ActionMenuResult ActionMenu::Show(const string &filePath)
{
    _filePath = filePath;
    cursorPosition = 0;

    while (true)
    {
        Display();
        u32 command = GetCommand();
        if (command & WPAD_BUTTON_DOWN)
        {
            cursorPosition++;
            if (cursorPosition >= nbItems)
                cursorPosition = nbItems - 1;
        }
        else if (command & WPAD_BUTTON_UP)
        {
            cursorPosition--;
            if (cursorPosition >= nbItems)
                cursorPosition = 0;
        }
        else if (command & WPAD_BUTTON_A)
            return DoConfirmation();
        else if (command & WPAD_BUTTON_B)
            cursorPosition = nbItems - 1;
    }
}

ActionMenuResult ActionMenu::DoConfirmation()
{
   bool isInNand= (Path::GetRootName(_filePath) == "wii");
   if (1 <= selectIndex && selectIndex < 3 && isInNand )
   {
       if(!Confirm("There is a risk if this action modify the NAND. Do you want to continue?"))
    	   return amResult_Cancel;
   }
   else if (selectIndex == 3)
   {
	   if(!Confirm("Are you sure you want to delete this element?"))
		   return amResult_Cancel;
   }
   else if(selectIndex == 5)
	   if(!Confirm("Are you sure you want to delete this title?"))
		   return amResult_Cancel;

   return (ActionMenuResult)selectIndex;
}

bool ActionMenu::Confirm(const string &message)
{
    cout << message << endl
    << "A: Confirm        B: Cancel" << endl;

    while (true)
    {
        u32 command = GetCommand();
        if (command & WPAD_BUTTON_A)
            return true;
        else if (command & WPAD_BUTTON_B)
            return false;
    }
}
