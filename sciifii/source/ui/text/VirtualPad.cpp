#include <wiiuse/wpad.h>
#include <ogc/pad.h>

#include <sciifii/ui/text/VirtualPad.h>

static bool padInitiated = false;

void VPAD_ScanPads()
{
  WPAD_ScanPads();
  PAD_ScanPads();
}

u32 VPAD_ButtonsDown(u32 chan)
{
  u32 buttonsDown = 0;

  u32 pressed = WPAD_ButtonsDown(chan);
  if (pressed & WPAD_BUTTON_A)
    buttonsDown |= vpb_Ok;
  if (pressed & WPAD_BUTTON_B)
    buttonsDown |= vpb_Cancel;
  if (pressed & WPAD_BUTTON_LEFT)
    buttonsDown |= vpb_Left;
  if (pressed & WPAD_BUTTON_RIGHT)
    buttonsDown |= vpb_Right;
  if (pressed & WPAD_BUTTON_UP)
    buttonsDown |= vpb_Up;
  if (pressed & WPAD_BUTTON_DOWN)
    buttonsDown |= vpb_Down;
  if (pressed & WPAD_BUTTON_HOME)
    buttonsDown |= vpb_Exit;

  pressed = PAD_ButtonsDown(chan);
  if (pressed & PAD_BUTTON_A)
    buttonsDown |= vpb_Ok;
  if (pressed & PAD_BUTTON_B)
    buttonsDown |= vpb_Cancel;
  if (pressed & PAD_BUTTON_LEFT)
    buttonsDown |= vpb_Left;
  if (pressed & PAD_BUTTON_RIGHT)
    buttonsDown |= vpb_Right;
  if (pressed & PAD_BUTTON_UP)
    buttonsDown |= vpb_Up;
  if (pressed & PAD_BUTTON_DOWN)
    buttonsDown |= vpb_Down;
  if (pressed & PAD_BUTTON_START)
    buttonsDown |= vpb_Exit;

  return buttonsDown;
}

void VPAD_Init()
{
  if(padInitiated)
    return;
  WPAD_Init();
  PAD_Init();
  padInitiated = true;
}

void VPAD_Shutdown()
{
  if(!padInitiated)
    return;

  WPAD_Shutdown();

  padInitiated = false;
}
