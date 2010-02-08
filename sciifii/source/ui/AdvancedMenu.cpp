#include "AdvancedMenu.h"
#include "Disclaimer.h"

#include "../Config.h"
#include <iostream>
#include <iomanip>
#include <wiiuse/wpad.h>

using namespace std;

AdvancedMenu::AdvancedMenu()
: MenuBase(),
  menuMaxLength(0),
  selectIndex(0)
{
    actions.push_back("Restore Tucha Bug");
    actions.push_back("Install cios rev17 (DL Bug Fix)");
    actions.push_back("Install the cioscorp");
    actions.push_back("Install firmware 4.2");
    actions.push_back("Start Installation");
	actions.push_back("Uninstall hacks and update to 4.2");
    actions.push_back("Exit");
	
	for(vector<string>::iterator ite = actions.begin(); ite != actions.end(); ite++)
	{
		if(ite->size() > menuMaxLength)
		  menuMaxLength = ite->size();
	}
}

void AdvancedMenu::Display()
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
			bool selected = GetConfig((AdvancedMenuResult)position);
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

AdvancedMenuResult AdvancedMenu::Show()
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
			AdvancedMenuResult item = (AdvancedMenuResult)cursorPosition;
			if(cursorPosition < 4)
			  ManageConfig(item);
			else
			  return item;
		}
        else if (command & WPAD_BUTTON_B)
            cursorPosition = nbItems - 1;
    }
}


void AdvancedMenu::ManageConfig(AdvancedMenuResult choice)
{
	switch(choice)
	{
		case amResult_RestoreTrucha:
			Config::RestoreTrucha(!Config::RestoreTrucha());
			break;
		case amResult_InstallCios:
			Config::InstallCios(!Config::InstallCios());
			break;
		case amResult_InstallCorp:
			Config::InstallCorp(!Config::InstallCorp());
			break;
		case amResult_Update:
			Config::UpdateSystem(!Config::UpdateSystem());
			break;
		default:
			break;
	}
	
	return;
}

bool AdvancedMenu::GetConfig(AdvancedMenuResult choice)
{
	switch(choice)
	{
		case amResult_RestoreTrucha:
			return Config::RestoreTrucha();
		case amResult_InstallCios:
			return Config::InstallCios();
		case amResult_InstallCorp:
			return Config::InstallCorp();
		case amResult_Update:
			return Config::UpdateSystem();
		default:
			return false;
	}
}