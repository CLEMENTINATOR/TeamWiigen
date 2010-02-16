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
	for(vector<option*>::iterator ite = Config::Options().begin(); ite != Config::Options().end(); ite++)
	{
		if((*ite)->text.size() > menuMaxLength)
		  menuMaxLength = (*ite)->text.size();
	}
}

void AdvancedMenu::Display()
{
	u32 position = 0;

    Disclaimer::Show();

	string red = "\x1b[31m";
	string green = "\x1b[32m";

	for(vector<option*>::iterator ite = Config::Options().begin(); ite != Config::Options().end(); ite++)
	{
		string choice = (*ite)->selected ? "Yes" : "No";
		string color = (*ite)->selected ? green : red;
		cout << (position++ == cursorPosition ? ">>>\t" : "   \t") << setw(menuMaxLength) << left << (*ite)->text << setw(0) << right << "\t" << color << choice << "\x1b[37m" << endl;
    }

	cout << endl << endl;

	cout << (position++ == cursorPosition ? ">>>\t" : "   \t") << "Go" << endl;
	cout << (position++ == cursorPosition ? ">>>\t" : "   \t") << "Exit" << endl;

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
			if(cursorPosition == nbItems - 1)
				return amResult_Exit;

			if(cursorPosition == nbItems - 2)
				return amResult_Exit;

			option* opt = Config::Options()[cursorPosition];
			opt->selected = !opt->selected;
		}
        else if (command & WPAD_BUTTON_B)
            cursorPosition = nbItems - 1;
    }
}
