#include <iostream>
#include <iomanip>

#include <Sciifii.h>

using namespace std;

AdvancedMenu::AdvancedMenu()
: MenuBase(),
  menuMaxLength(0),
  selectIndex(0)
{
	vector<option*> options = Config::Options();
	for(vector<option*>::iterator ite = options.begin(); ite != options.end(); ite++)
	{
		if((*ite)->text.size() > menuMaxLength)
		  menuMaxLength = (*ite)->text.size();
		if((*ite)->hidden==false) opt.push_back(*ite);
	}
}

void AdvancedMenu::Display()
{
	u32 position = 0;

    Disclaimer::Show();

	string red = "\x1b[31m";
	string green = "\x1b[32m";


	for(vector<option*>::iterator ite = opt.begin(); ite != opt.end(); ite++)
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
        else if (command & (vpb_Ok | vpb_Left | vpb_Right))
        {
			if((cursorPosition == nbItems - 1) && (command & vpb_Ok))
				return amResult_Exit;

			if((cursorPosition == nbItems - 2) && (command & vpb_Ok))
				return amResult_Continue;

			option* opti = opt[cursorPosition];
			opti->selected = !opti->selected;
		}
        else if (command & vpb_Cancel)
            cursorPosition = nbItems - 1;
    }
}
