#include "Disclaimer.h"

#include <iostream>

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
}
