#include "Disclaimer.h"

#include <iostream>
#include <ogc/conf.h>

using namespace std;

void Disclaimer::Show()
{
  //clear screen
  cout << "\x1b[2J";
  cout << "\x1b[2;0H";


  cout << endl << endl;

  cout << "Sciifii Installer v1 based on cios corp v4.0" << endl
	   << "Made by Arasium, Teton and Fanta." << endl
	   << "Tested by Jicay, JeanMi59226, Vlad and Thetataz (and many others)." << endl
	   << "Special thanks to Waninkoko for his help" << endl
	   << "Thanks to da_letter_a for the cios corp knowledge." << endl
	   << "mail: TeamWiigen@googlemail.com" << endl << endl
	   << "This app comes with no warranty"<< endl
	   << "So if you don't know what you're doing here, get out NOW !" << endl << endl;
	   
	   
	s32 region = CONF_GetRegion();
	cout << "Detected wii region: ";
	
	switch(region)  //channels
	{
		case CONF_REGION_JP:
			cout << "Jap";
			break;
		case CONF_REGION_US:
			cout << "US";
			break;
		case CONF_REGION_EU:
			cout << "Eur";
			break;
		case CONF_REGION_KR:
			cout << "Kor";
			break;
		default:
			cout << "Unknown!!! Please exit!";
	}
	
	cout << endl << endl;
}
