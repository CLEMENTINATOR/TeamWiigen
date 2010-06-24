#include <libwiisys.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace Libwiisys::System::Event;
using namespace Libwiisys::System::Patching;
using namespace Libwiisys::Exceptions;

ModulePatch::ModulePatch(const u8* patch, const u32 length, const std::string &module)
    : Patch(module),
    _patch(NULL),
    _length(length)
{
  if(!patch)
    throw Exception("You need to indicate a patch.", -1);
	
  _patch = new u8[length];
  memcpy(_patch, patch, length);
}

ModulePatch::ModulePatch(const ModulePatch& patch)
    : Patch(patch),
    _patch(NULL),
    _length(patch._length)
{
  _patch = new u8[patch._length];
  memcpy(_patch, patch._patch, patch._length);
}

ModulePatch& ModulePatch::operator=(const ModulePatch& patch)
{
  Patch::operator=(patch);

  delete[] _patch;
  _patch = NULL;
	
  _patch = new u8[patch._length];
  memcpy(_patch, patch._patch, patch._length);

  _length = patch._length;
  
  return *this;
}

ModulePatch::~ModulePatch()
{
  delete[] _patch;
}

u32 ModulePatch::Patching(TitleEventArgs &processControl) const
{
  processControl.buffer.Clear();
  processControl.buffer.Append(_patch, _length);
  processControl.tmdInfo->size = _length;
  
  return 1;
}
