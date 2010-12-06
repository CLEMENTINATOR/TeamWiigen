#include <Libwui/Resources/FontResource.hpp>
#include <malloc.h>
#include <Libwiisys/IO/File.h>

using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::IO;

FontResource::FontResource(const string& fontPath)
    : _font(NULL)
{
  _resource = File::ReadToEnd(fontPath);
}

FontResource::FontResource(const u8* data, u32 size)
    : _font(NULL),
    _resource(data, size)
{}

FontResource::~FontResource()
{
  if(_font)
    delete _font;
	_resource.Clear();
}

bool FontResource::IsInitialized()
{
  return _font != NULL;
}

void FontResource::Initialize(bool cacheAll, uint8_t textureFormat, uint8_t vertexIndex)
{
  _font = new FreeTypeGX(textureFormat, vertexIndex);
  _font->loadFont((u8*)_resource.Content(), _resource.Length(), 12,cacheAll);
}

FreeTypeGX* FontResource::Font()
{
  return _font;
}
