#include <system/SimplePatch.h>
#include <exception/Exception.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

SimplePatch::SimplePatch(const u8* pattern,const u8* patch,const u32 length, const std::string &module)
    : Patch(module),
	_pattern(NULL),
    _patch(NULL),
    _length(length)
{
  if(!pattern || !patch)
    throw Exception("You need to indicate a pattern and a patch.", -1);

  _pattern = new u8[length];
  memcpy(_pattern, pattern, length);

  _patch = new u8[length];
  memcpy(_patch, patch, length);
}

SimplePatch::SimplePatch(const SimplePatch& patch)
    : Patch(patch),
	_pattern(NULL),
    _patch(NULL),
    _length(patch._length)
{
  _pattern = new u8[patch._length];
  memcpy(_pattern, patch._pattern, patch._length);

  _patch = new u8[patch._length];
  memcpy(_patch, patch._patch, patch._length);
}

SimplePatch& SimplePatch::operator=(const SimplePatch& patch)
{
  Patch::operator=(patch);

  delete[] _pattern;
  _pattern = NULL;

  _pattern = new u8[patch._length];
  memcpy(_pattern, patch._pattern, patch._length);

  delete[] _patch;
  _patch = NULL;

  _patch = new u8[patch._length];
  memcpy(_patch, patch._patch, patch._length);

  _length = patch._length;

  return *this;
}

SimplePatch::~SimplePatch()
{
  delete[] _pattern;

  delete[] _patch;
}

u32 SimplePatch::Patching(TitleEventArgs &processControl) const
{
	u32 nbPatch = 0;

	for (u32 cnt = 0; cnt < processControl.buffer.Length() - _length; cnt++)
	{
	  u8 *ptr = (u8*)processControl.buffer.Content() + cnt;

	  if (!memcmp(ptr, _pattern, _length))
	  {
		/* Replace code */
		memcpy(ptr, _patch, _length);
		cnt += _length;
		nbPatch++;
	  }
	}

  return nbPatch;
}

SimplePatch* SimplePatch::ES_HashCheck_Old()
{
  u8 oldCode[] = { 0x20, 0x07, 0x23, 0xA2 };
  u8 newCode[] = { 0x20, 0x00, 0x23, 0xA2 };

  static SimplePatch p(oldCode, newCode, 4, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_HashCheck_New()
{
  u8 oldCode[] = { 0x20, 0x07, 0x4B, 0x0B };
  u8 newCode[] = { 0x20, 0x00, 0x4B, 0x0B };

  static SimplePatch p(oldCode, newCode, 4, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_Identify()
{
  u8 oldCode[] = { 0x28, 0x03, 0xD1, 0x23 };
  u8 newCode[] = { 0x23, 0x03, 0x46, 0xC0 };

  static SimplePatch p(oldCode, newCode, 4, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_MEM2Protection()
{
  u8 oldCode[] = { 0xB5, 0x00, 0x4B, 0x09, 0x22, 0x01, 0x80, 0x1A, 0x22, 0xF0 };
  u8 newCode[] = { 0xB5, 0x00, 0x4B, 0x09, 0x22, 0x00, 0x80, 0x1A, 0x22, 0xF0 };

  static SimplePatch p(oldCode, newCode, 10, "ES");
  return &p;
}

SimplePatch* SimplePatch::FFS_PermsCheck()
{
  u8 oldCode[] = { 0x42, 0x8B, 0xD0, 0x01, 0x25, 0x66 };
  u8 newCode[] = { 0x42, 0x8B, 0xE0, 0x01, 0x25, 0x66 };

  static SimplePatch p(oldCode, newCode, 6, "FFS");
  return &p;
}

SimplePatch* SimplePatch::ES_OpenTitleContent1()
{
  u8 oldCode[] = { 0x9D, 0x05, 0x42, 0x9D, 0xD0, 0x03 };
  u8 newCode[] = { 0x9D, 0x05, 0x42, 0x9D, 0xE0, 0x03 };

  static SimplePatch p(oldCode, newCode, 6, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_OpenTitleContent2()
{
  u8 oldCode[] = { 0xD4, 0x01, 0x4C, 0x36, 0xE0, 0x3B };
  u8 newCode[] = { 0xE0, 0x01, 0x4C, 0x36, 0xE0, 0x3B };

  static SimplePatch p(oldCode, newCode, 6, "ES");
  return &p;


}

SimplePatch* SimplePatch::ES_ReadContent()
{
  u8 oldCode[] = { 0xFC, 0x0F, 0xB5, 0x30, 0x1C, 0x14, 0x1C, 0x1D, 0x4B, 0x0E, 0x68, 0x9B,
                   0x2B, 0x00, 0xD0, 0x03, 0x29, 0x00, 0xDB, 0x01, 0x29, 0x0F, 0xDD, 0x01
                 };
  u8 newCode[] = { 0xFC, 0x0F, 0xB5, 0x30, 0x1C, 0x14, 0x1C, 0x1D, 0x4B, 0x0E, 0x68, 0x9B,
                   0x2B, 0x00, 0x46, 0xC0, 0x29, 0x00, 0x46, 0xC0, 0x29, 0x0F, 0xE0, 0x01
                 };


  static SimplePatch p(oldCode, newCode, 24, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_CloseContent()
{
  u8 oldCode[] = { 0xB5, 0x10, 0x4B, 0x10, 0x68, 0x9B, 0x2B, 0x00, 0xD0,
                   0x03, 0x29, 0x00, 0xDB, 0x01, 0x29, 0x0F, 0xDD, 0x01
                 };
  u8 newCode[] = { 0xB5, 0x10, 0x4B, 0x10, 0x68, 0x9B, 0x2B, 0x00, 0x46,
                   0xC0, 0x29, 0x00, 0x46, 0xC0, 0x29, 0x0F, 0xE0, 0x01
                 };

  static SimplePatch p(oldCode, newCode, 18, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_SetUIDCheck()
{
  u8 oldCode[] = { 0xD1, 0x2A, 0x1C, 0x39 };
  u8 newCode[] = { 0x46, 0xC0, 0x1C, 0x39 };

  static SimplePatch p(oldCode, newCode, 4, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_TitleVersionCheck()
{
  u8 oldCode[] = { 0xD2, 0x01, 0x4E, 0x56 };
  u8 newCode[] = { 0xE0, 0x01, 0x4E, 0x56 };

  static SimplePatch p(oldCode, newCode, 4, "ES");
  return &p;
}

SimplePatch* SimplePatch::ES_TitleDeleteCheck()
{
  u8 oldCode[] = { 0xD8, 0x00, 0x4A, 0x04 };
  u8 newCode[] = { 0xE0, 0x00, 0x4A, 0x04 };

  static SimplePatch p(oldCode, newCode, 4, "ES");
  return &p;
}

SimplePatch* SimplePatch::DIP_UnencryptedLimit()
{
  u8 oldCode[] = { 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0A, 0x00, 0x00 };
  u8 newCode[] = { 0x7E, 0xD4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0A, 0x00, 0x00 };

  static SimplePatch p(oldCode, newCode, 12, "DIP");
  return &p;
}

SimplePatch* SimplePatch::DIP_EnableDvdVideo()
{
  u8 oldCode[] = { 0x20, 0x01, 0xF0, 0x05 };
  u8 newCode[] = { 0x20, 0x00, 0xF0, 0x05 };

  static SimplePatch p(oldCode, newCode, 4, "DIP");
  return &p;
}

/* Other patches */
SimplePatch* SimplePatch::KoreanKey_EnablePatch()
{
  u8 oldCode[] = { 0x28, 0x00, 0xD0, 0x0A, 0x20, 0x3A, 0x1C, 0x21 };
  u8 newCode[] = { 0x28, 0x00, 0xE0, 0x0A, 0x20, 0x3A, 0x1C, 0x21 };

  static SimplePatch p(oldCode, newCode, 8);
  return &p;
}

SimplePatch* SimplePatch::getPatch(const std::string &s)
{
if(s=="ES_HashCheck_Old") return ES_HashCheck_Old();
else if(s=="ES_HashCheck_New") return ES_HashCheck_New();
else if(s=="ES_Identify") return ES_Identify();
else if(s=="ES_OpenTitleContent1") return ES_OpenTitleContent1();
else if(s=="ES_OpenTitleContent2") return ES_OpenTitleContent2();
else if(s=="ES_ReadContent") return ES_ReadContent();
else if(s=="ES_CloseContent") return ES_CloseContent();
else if(s=="ES_SetUIDCheck") return ES_SetUIDCheck();
else if(s=="ES_TitleVersionCheck") return ES_TitleVersionCheck();
else if(s=="ES_TitleDeleteCheck") return ES_TitleDeleteCheck();
else if(s=="ES_MEM2Protection") return ES_MEM2Protection();
else if(s=="FFS_PermsCheck") return FFS_PermsCheck();
else if(s=="DIP_UnencryptedLimit") return DIP_UnencryptedLimit();
else if(s=="DIP_EnableDvdVideo") return DIP_EnableDvdVideo();
else if(s=="KoreanKey_EnablePatch") return KoreanKey_EnablePatch();
else throw Exception("Unknown prebuld patch",-1);

return NULL;
}
