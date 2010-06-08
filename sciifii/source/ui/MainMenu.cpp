#include "MainMenu.h"
#include "Disclaimer.h"

#include "../Config.h"
#include <iostream>
#include <iomanip>
#include "VirtualPad.h"

using namespace std;

MainMenu::MainMenu()
: MenuBase(),
  menuMaxLength(0),
  selectIndex(0)
{
	vector<mode*> modes = Config::Modes();
    for(vector<mode*>::iterator ite = modes.begin(); ite != modes.end(); ite++)
	{
		if((*ite)->text.size() > menuMaxLength)
		  menuMaxLength = (*ite)->text.size();
	}
}

void MainMenu::Display()
{
	u32 position = 0;
	
    Disclaimer::Show();
	
	cout << endl << endl << Config::MenuMessage() << endl << endl;

	string red = "\x1b[31m";
	string green = "\x1b[32m";
	
	vector<mode*> modes = Config::Modes();
	for(vector<mode*>::iterator ite = modes.begin(); ite != modes.end(); ite++)
		cout << (position++ == cursorPosition ? ">>>\t" : "   \t") << (*ite)->text << endl;

	cout << endl << endl;

	if(Config::UseAdvancedMode())
		cout << (position++ == cursorPosition ? ">>>\t" : "   \t") << "Advanced settings" << endl;


	cout << (position++ == cursorPosition ? ">>>\t" : "   \t") << "Exit" << endl;

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
        if (command & vpb_Down)
        {
            cursorPosition++;
            if (cursorPosition >= nbItems)
                cursorPosition = nbItems - 1;
        }
        else if (command & vpb_Up)
        {
            cursorPosition--;
            if (cursorPosition >= nbItems)
                cursorPosition = 0;
        }
        else if (command & vpb_Ok)
			return ManageConfig(cursorPosition);
        else if (command & vpb_Cancel)
            cursorPosition = nbItems - 1;
    }
}

MainMenuResult MainMenu::ManageConfig(u32 selection)
{
	if(selection == nbItems - 1)
		return mmResult_Exit;

	if(Config::UseAdvancedMode() && selection == nbItems - 2)
		return mmResult_Advanced;

	Config::ApplyMode(*Config::Modes()[selection]);

	return mmResult_Nothing;
}
