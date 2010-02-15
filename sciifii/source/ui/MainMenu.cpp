#include "MainMenu.h"
#include "Disclaimer.h"

#include "../Config.h"
#include <iostream>
#include <iomanip>
#include <wiiuse/wpad.h>

using namespace std;

MainMenu::MainMenu()
: MenuBase(),
  menuMaxLength(0),
  selectIndex(0)
{
    actions.push_back("Hack your wii!!");
    actions.push_back("Hack your wii (no corp)!!");
    actions.push_back("Hack your wii (advanced mode)!!");
    actions.push_back("Unhack your wii.");
    actions.push_back("Exit");

	for(vector<string>::iterator ite = actions.begin(); ite != actions.end(); ite++)
	{
		if(ite->size() > menuMaxLength)
		  menuMaxLength = ite->size();
	}
}

void MainMenu::Display()
{
	u32 position = 0;

    Disclaimer::Show();

	cout << endl << endl << "All these options will also update your wii to 4.2." << endl
		 << "If you don't want to update, use advanced mode." << endl << endl;

	string red = "\x1b[31m";
	string green = "\x1b[32m";

    for (vector<string>::iterator ite = actions.begin(); ite != actions.end(); ite ++)
    {
		//add config result here
		cout << (position == cursorPosition ? ">>>\t" : "   \t") << *ite << endl;
        position++;
    }

    nbItems = position;

    // Wait for the next frame
    VIDEO_WaitVSync();
}

MainMenuResult MainMenu::Show()
{
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
        {
			MainMenuResult item = (MainMenuResult)cursorPosition;
			ManageConfig(item);
			return item;
		}
        else if (command & WPAD_BUTTON_B)
            cursorPosition = nbItems - 1;
    }
}


void MainMenu::ManageConfig(MainMenuResult choice)
{
	switch(choice)
	{
		case mmResult_HackNoCorp:
		Config::InstallCorp(false); //the system will be overriden, so we can skip this to reduce operation time
		case mmResult_Unhack:
			Config::InstallCorp(false);
			Config::InstallGX(false);
			break;
		default:
			break;
	}

	return;
}
