#include "ConfigMenu.h"
#include "../../business/ConfigurationManager.h"
#include <iostream>
#include <iomanip>
#include <wiiuse/wpad.h>

using namespace std;

void ConfigMenu::Show()
{
	while(true)
	{
		Display();
		u32 command = GetCommand();

		if(command & WPAD_BUTTON_DOWN)
		{
			cursorPosition++;
			if(cursorPosition >= nbItems)
				cursorPosition = nbItems - 1;
		}
		else if(command & WPAD_BUTTON_UP)
		{
			cursorPosition--;
			if(cursorPosition >= nbItems)
				cursorPosition = 0;
		}
		else if(command & WPAD_BUTTON_B)
			cursorPosition = 1;
		else if(command & WPAD_BUTTON_HOME)
			cursorPosition = 2;
		else if(command & WPAD_BUTTON_A)
		{
			if(cursorPosition == 0)
				ConfigurationManager::GetCurrent().SetEnsureSecurity(!ConfigurationManager::GetCurrent().IsEnSureSecurity());
			else if(cursorPosition == 1)
				break;
			else
				SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
		}
	}
}

void ConfigMenu::Display()
{
	ConfigurationManager &config = ConfigurationManager::GetCurrent();

	//clear screen
	cout << "\x1b[2J";
	cout << "\x1b[2;0H";

	// nom de la team
	cout << "================================================" << endl
	     << "File Browser made by Arasium, Teton and Fanta" << endl
	     << "Thank to all the staff (beta testers and others)" << endl
	     << "================================================" << endl << endl;

	//legend
	cout << "A: Modify the selected option/Execute the selected item" << endl
		 << "B: Move the cursor to the \"return to browser\" item" << endl
		 << "HOME: Move the cursor to the \"Exit browser\" item" << endl << endl;

	u32 position = 0;

	cout << (position++ == cursorPosition ? ">>>   " : "      ") << "Nand Security:";
	
	if(config.IsEnSureSecurity())
		cout << "On" << endl;
	else
		cout << "Off" << endl;
		
	cout << (position++ == cursorPosition ? ">>>   " : "      ") << "Return to browser" << endl;
	cout << (position++ == cursorPosition ? ">>>   " : "      ") << "Exit browser" << endl;

	nbItems = position;
}
