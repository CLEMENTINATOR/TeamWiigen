#include <Libwui/Resources/FontResource.hpp>
#include <malloc.h>
#include <Libwiisys/IO/File.h>
#include <vector>
#include <Libwiisys/Exceptions/Exception.h>

using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
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

bool FontResource::IsInitialized(s32 size)
{
  return _fonts.find(size) != _fonts.end();
}

void FontResource::Initialize(s32 size, bool cacheAll, uint8_t textureFormat , uint8_t vertexIndex )
{
  FreeTypeGX *font = new FreeTypeGX(textureFormat, vertexIndex);
  font->loadFont((u8*)_resource.Content(), _resource.Length(), size, cacheAll);
  _cacheUsed[size] = false;
  _fonts[size] = font;
}


FreeTypeGX* FontResource::Font(s32 size)
{
  if(_fonts.find(size) == _fonts.end())
    throw Exception("Font resource not initialized");

  _cacheUsed[size] = true;
  return _fonts[size];
}

void FontResource::Clean()
{
  vector<s32> toDelete;

  for(map<s32,bool>::iterator ite = _cacheUsed.begin(); ite != _cacheUsed.end(); ite++)
    if(!ite->second)
    {
      delete _fonts[ite->first];
      _fonts.erase(ite->first);
      toDelete.push_back(ite->first);
    }
    else
      _cacheUsed[ite->first] = false;

  for(vector<s32>::iterator ite = toDelete.begin(); ite != toDelete.end(); ite++)
    _cacheUsed.erase(*ite);
}
