#include <iostream>

#include <Sciifii.h>

using namespace std;

DynamicMenu::DynamicMenu(TiXmlElement* node)
: MenuBase(),
  selectIndex(0)
{}

void DynamicMenu::Display()
{
  Disclaimer::Show();

	for(vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
	{
		(*ite)->Render();
		cout << endl;	
  }

	// Wait for the next frame
	VIDEO_WaitVSync();
}

NavigateEventArgs DynamicMenu::Show()
{
		nav.NavigateTo = "menu";
		nav.MenuId = _menuId;
		
    while (nav.NavigateTo == "menu" && nav.MenuId == _menuId)
    {
        Display();
        u32 command = GetCommand();
				u32 nextItem = selectIndex;
        if (command & vpb_Down)
        {
					do
					{
						nextItem++;
					} while(nextItem < items.size() && !items.at(nextItem)->Selectable);
					
					if(nextItem < items.size())
          {
						items.at(selectIndex)->Selected = false;
						selectIndex = nextItem;
						items.at(selectIndex)->Selected = true;
					}
        }
        else if (command & vpb_Up)
        {
          do
					{
						nextItem--;
					} while(nextItem >= 0 && !items.at(nextItem)->Selectable);
					
					if(nextItem >= 0)
          {
						items.at(selectIndex)->Selected = false;
						selectIndex = nextItem;
						items.at(selectIndex)->Selected = true;
					}
        }
        else
        {
					items.at(selectIndex)->ButtonPressed(command);
				}
    }
		
		return nav;
}
