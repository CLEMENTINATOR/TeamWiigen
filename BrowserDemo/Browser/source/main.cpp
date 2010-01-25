//#define TEXTMODE
#include <ogcsys.h>
#ifdef TEXTMODE

#include "maintext.h"

//---------------------------------------------------------------------------------
int main(int argc, char **argv)
{
//---------------------------------------------------------------------------------
	maintext(argc, argv);
}

#else

#include "mainui.h"

//---------------------------------------------------------------------------------
int main(int argc, char **argv)
{
//---------------------------------------------------------------------------------
	mainui(argc, argv);
	SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
}

#endif
