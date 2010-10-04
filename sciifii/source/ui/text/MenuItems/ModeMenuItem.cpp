#include <iostream>
#include <Sciifii.h>

using namespace std;

ModeMenuItem::ModeMenuItem(TiXmlElement* node)
{}

void ButtonPressed(u32 button)
{
	if(button & vpb_Ok)
	{
		OptionEventArgs arg;
		args.Incremental = false;
		for(vector<string>::iterator ite =  _options.begin(); ite != _option.end(); ite++)
			args.Options.push_back(Option(*ite,true));
			
		OnModifyOption(args);
		StartMenuItem::ButtonPressed(button);
	}
}