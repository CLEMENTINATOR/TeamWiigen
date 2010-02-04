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
    actions.push_back("Restore Tucha Bug");
    actions.push_back("Install cios rev17 (DL Bug Fix)");
    actions.push_back("Install the cioscorp");
    actions.push_back("Install firmware 4.2");
    actions.push_back("Start Installation");
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
		if(position < 4)
		{
			bool selected = GetConfig((MainMenuResult)position);
			string choice = selected ? "Yes" : "No";
			string color = selected ? green : red;
			cout << (position == cursorPosition ? ">>>\t" : "   \t") << setw(menuMaxLength) << left << *ite << setw(0) << right << "\t" << color << choice << "\x1b[37m" << endl;
		}
		else
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
        else if (command & (WPAD_BUTTON_A | WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT))
        {
			MainMenuResult item = (MainMenuResult)cursorPosition;
			if(cursorPosition < 4)
			  ManageConfig(item);
			else
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
		case mmResult_RestoreTrucha:
			Config::RestoreTrucha(!Config::RestoreTrucha());
			break;
		case mmResult_InstallCios:
			Config::InstallCios(!Config::InstallCios());
			break;
		case mmResult_InstallCorp:
			Config::InstallCorp(!Config::InstallCorp());
			break;
		case mmResult_Update:
			Config::UpdateSystem(!Config::UpdateSystem());
			break;
		default:
			break;
	}
	
	return;
}

bool MainMenu::GetConfig(MainMenuResult choice)
{
	switch(choice)
	{
		case mmResult_RestoreTrucha:
			return Config::RestoreTrucha();
		case mmResult_InstallCios:
			return Config::InstallCios();
		case mmResult_InstallCorp:
			return Config::InstallCorp();
		case mmResult_Update:
			return Config::UpdateSystem();
		default:
			return false;
	}
}