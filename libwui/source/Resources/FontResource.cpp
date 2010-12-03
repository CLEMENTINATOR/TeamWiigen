#include <Libwui/Resources/FontResource.hpp>
#include <malloc.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <vector>

using namespace Libwui::Resources;
using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

FontResource::FontResource(const string& fontPath)
{
  _resource = File::ReadToEnd(fontPath);
}

FontResource::FontResource(const u8* data, u32 size)
    : _resource(data, size)
{}

FontResource::~FontResource()
{
  for(map<s32,FreeTypeGX*>::iterator ite = _fonts.begin(); ite != _fonts.end(); ite++)
	delete ite->second;
}

bool FontResource::IsInitialized(s32 size)
{
  return _fonts.find(size) != _fonts.end();
}

void FontResource::Initialize(s32 size, bool cacheAll, uint8_t textureFormat, uint8_t vertexIndex)
{
  FreeTypeGX *font = new FreeTypeGX(textureFormat, vertexIndex);
  font->loadFont((u8*)_resource.Content(), _resource.Length(), size, cacheAll);
  _cacheCount[size] = 0;
  _fonts[size] = font;
}

FreeTypeGX* FontResource::Font(s32 size)
{
  if(_fonts.find(size) == _fonts.end())
    throw Exception("Font resource not initialized");
	
  _cacheCount[size] = 1;
  return _fonts[size];
}

void FontResource::Clean()
{
	vector<s32> toDelete;

	for(map<s32,u32>::iterator ite = _cacheCount.begin(); ite != _cacheCount.end(); ite++)
		if(ite->second == 0)
		{
				_fonts[ite->first];
				_fonts.erase(ite->first);
				toDelete.push_back(ite->first);
		}
		else
			_cacheCount[ite->first] = 0;
		
	for(vector<s32>::iterator ite = toDelete.begin(); ite != toDelete.end(); ite++)
		_cacheCount.erase(*ite);
}