#include <Libwui/Events/TrackBarEventArgs.hpp>

using namespace Libwui::Events;

TrackBarEventArgs::TrackBarEventArgs(u32 val) : _value(val)
{}

u32 TrackBarEventArgs::Value()
{
  return _value;
}
