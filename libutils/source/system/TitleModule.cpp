#include <system/TitleModule.h>

TitleModule::TitleModule(const u8* buffer, const u64 length, const s32 requiredPosition)
: Buffer(buffer, length),
  _position(requiredPosition)
{}

TitleModule::TitleModule(const TitleModule& m)
: Buffer(m), _position(m._position)
{}

bool TitleModule::IsPositionRequired() const
{
	return _position > 0;
}

u32 TitleModule::Position() const
{
	return _position;
}