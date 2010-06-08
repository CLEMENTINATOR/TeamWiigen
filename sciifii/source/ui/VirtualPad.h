#ifndef _VIRTUAL_PAD_H_
#define _VIRTUAL_PAD_H_

#include <gctypes.h>

enum VPadButtons
{
	vpb_Up,
	vpb_Down,
	vpb_Left,
	vpb_Right,
	vpb_Ok,
	vpb_Cancel,
	vpb_Exit,
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