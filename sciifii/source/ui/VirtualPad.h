#ifndef _VIRTUAL_PAD_H_
#define _VIRTUAL_PAD_H_

#include <gctypes.h>

enum VPadButtons
{
	vpb_Up = 1,
	vpb_Down = 2,
	vpb_Left = 4,
	vpb_Right = 8,
	vpb_Ok = 16,
	vpb_Cancel = 32,
	vpb_Exit = 64,
};

enum VPadChan
{
	vbc_Chan0 = 0,
	vbc_Chan1 = 1,
	vbc_Chan2 = 2,
	vbc_Chan3 = 3,
};

void VPAD_ScanPads();
u32 VPAD_ButtonsDown(u32 chan);


#endif