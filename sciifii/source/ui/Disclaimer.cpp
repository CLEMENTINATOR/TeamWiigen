#include "Disclaimer.h"
#include "../Config.h"
#include <iostream>
#include <ogc/conf.h>

using namespace std;

void Disclaimer::Show()
{
  //clear screen
  cout << "\x1b[2J";
  cout << "\x1b[2;0H";


  cout << endl << endl;

  cout << Config::DisclaimerText() << endl << endl;
	   
	   
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
