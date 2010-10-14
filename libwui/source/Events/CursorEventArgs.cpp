#include <libwui/Events/CursorEventArgs.h>

using namespace Libwui::Events;
using namespace Libwui::Device;

CursorEventArgs::CursorEventArgs(PadController& controller) : pad(&controller)
{}

PadController& CursorEventArgs::Controller()
{
  return *pad;
}
