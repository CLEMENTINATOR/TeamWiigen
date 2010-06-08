#include <wiiuse/wpad.h>
#include <ogc/pad.h>
#include "VirtualPad.h"

void VPAD_ScanPads()
{
	WPAD_ScanPads();
	PAD_ScanPads();
}

u32 VPAD_ButtonsDown(u32 chan)
{
	u32 buttonsDown = 0;
	
	u32 pressed = WPAD_ButtonsDown(chan);
	if (pressed & WPAD_BUTTON_A) buttonsDown |= vpb_Ok;
	if (pressed & WPAD_BUTTON_B) buttonsDown |= vpb_Cancel;
	if (pressed & WPAD_BUTTON_LEFT) buttonsDown |= vpb_Down;
	if (pressed & WPAD_BUTTON_RIGHT) buttonsDown |= vpb_Up;
	if (pressed & WPAD_BUTTON_UP) buttonsDown |= vpb_Left;
	if (pressed & WPAD_BUTTON_DOWN) buttonsDown |= vpb_Right;
	if (pressed & WPAD_BUTTON_HOME) buttonsDown |= vpb_Exit;
	
	pressed = PAD_ButtonsDown(chan);
	if (pressed & PAD_BUTTON_A) buttonsDown |= vpb_Ok;
	if (pressed & PAD_BUTTON_B) buttonsDown |= vpb_Cancel;
	if (pressed & PAD_BUTTON_LEFT) buttonsDown |= vpb_Down;
	if (pressed & PAD_BUTTON_RIGHT) buttonsDown |= vpb_Up;
	if (pressed & PAD_BUTTON_UP) buttonsDown |= vpb_Left;
	if (pressed & PAD_BUTTON_DOWN) buttonsDown |= vpb_Right;
	if (pressed & PAD_BUTTON_START) buttonsDown |= vpb_Exit;
	
	return buttonsDown;
}