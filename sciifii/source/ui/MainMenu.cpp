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
		case mmResult_Hack:
			Config::RestoreTrucha(true);
			Config::InstallCios(true);
			Config::InstallCorp(true);
			Config::UpdateSystem(true);
			break;
		case mmResult_HackNoCorp:
		case mmResult_Unhack:
			Config::RestoreTrucha(true);
			Config::InstallCios(true);
			Config::InstallCorp(false);
			Config::UpdateSystem(true);
			break;
		default:
			break;
	}
	
	return;
}