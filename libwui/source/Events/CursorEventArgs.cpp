#include <libwui.h>

using namespace UI::Events;
using namespace UI::Device;

CursorEventArgs::CursorEventArgs(PadController& controller) : pad(&controller)
{}

PadController& CursorEventArgs::Controller()
{
	return *pad;
}
