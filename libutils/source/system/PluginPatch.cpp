#include <system/PluginPatch.h>
#include <system/Title.h>
#include <exception/Exception.h>
#include <stdlib.h>
#include <string.h>

#include <elf_abi.h>

using namespace std;

PluginPatch::PluginPatch(const Buffer& plugin, const u32 offset, const u32 bssNewSize, const std::string &module)
    : Patch(module),
	_plugin(plugin),
    _offset(offset),
    _bssNewSize(bssNewSize),
    _commandHandles(),
	_newProgramSection(NULL),
	_replaceSection(0)
{}

PluginPatch::PluginPatch(const PluginPatch& patch)
    : Patch(patch),
	_plugin(patch._plugin),
    _offset(patch._offset),
    _bssNewSize(patch._bssNewSize),
    _commandHandles(patch._commandHandles),
	_newProgramSection(NULL),
	_replaceSection(patch._replaceSection)
{
	if(patch._newProgramSection)
	{
		_newProgramSection = new Elf32_Phdr(*(patch._newProgramSection));
	}
}

PluginPatch::PluginPatch(const Buffer& plugin, Elf32_Phdr newHeader , const std::string &module, u32 replaceSection)
: Patch(module),
  _plugin(plugin),
  _offset(0),
  _bssNewSize(0),
  _commandHandles(),
  _newProgramSection(NULL),
  _replaceSection(replaceSection)
{
	_newProgramSection = new Elf32_Phdr(newHeader);
}

PluginPatch& PluginPatch::operator=(const PluginPatch& patch)
{
  Patch::operator=(patch);
  
  if(_newProgramSection)
	delete _newProgramSection;
	
  _plugin = patch._plugin;
  _offset = patch._offset;
  _bssNewSize = patch._bssNewSize;
  _commandHandles = patch._commandHandles;
  _replaceSection = patch._replaceSection;
  
  if(patch._newProgramSection)
	_newProgramSection = new Elf32_Phdr(*(patch._newProgramSection));
  
  return *this;
}

PluginPatch::~PluginPatch()
{
	if(_newProgramSection)
		delete _newProgramSection;
}

void PluginPatch::DefineCommandHandle(SimplePatch handle)
{
	_commandHandles.push_back(handle);
}

bool PluginPatch::IsElf(u8* buffer) const
{
	Elf32_Ehdr* header = (Elf32_Ehdr*)buffer;
	if (header->e_ident[0] == ELFMAG0
		&& header->e_ident[1] == ELFMAG1
		&& header->e_ident[2] == ELFMAG2
		&& header->e_ident[3] == ELFMAG3)
		return true;

	return false;
}

u32 PluginPatch::FindIOSVersionIndex(const Buffer& b) const
{
  string str = "$IOSVersion:";
  char* buf = (char*)b.Content();
  u32 skipedModules = 0;
  
  for (u64 cnt = 0; cnt < (b.Length() - str.size()); cnt++)
      /* Module string found */
      if (strncmp(str.c_str(), buf + cnt, str.length()) == 0)
	  {
	    cnt += str.length();
		while(buf[cnt] == ' ')
		  cnt++;
		if (strncmp(AllowedModule.c_str(), buf + cnt, AllowedModule.length()) == 0)
          return skipedModules;
		else
		  skipedModules++;
	  }

  throw Exception("IOS Module not found.", skipedModules);
}

u32 PluginPatch::FindPlugedSegment(u8* elf, u32 moduleToSkip) const
{
	Elf32_Ehdr* header = (Elf32_Ehdr*)elf;
	Elf32_Word segmentSize = 0;
	bool found = false;
	u32 segmentIndex = 0;
	u32 skipedModules = 0;
	
	for(u32 phIndex = 0; phIndex < header->e_phnum; phIndex++)
	{
		Elf32_Phdr* ph = (Elf32_Phdr*)(elf + header->e_phoff + phIndex * header->e_phentsize);
		if(ph->p_type == PT_LOAD && ph->p_vaddr != 0 && ph->p_filesz < _offset)
		{
			if(ph->p_filesz == 0)
				skipedModules++;
			else if(skipedModules == moduleToSkip)
			{
				if(ph->p_filesz > segmentSize)
				{
					segmentIndex = phIndex;
					segmentSize = ph->p_filesz;
					found = true;
				}
			}
			else if(skipedModules > moduleToSkip)
			  break;
		}
	}
	
	if(!found)
		throw Exception("No segment found!" , -1);
		
	return segmentIndex;
}

u32 PluginPatch::FindBssSegment(u8* elf, u32 moduleToSkip) const
{
	Elf32_Ehdr* header = (Elf32_Ehdr*)elf;
	u32 skipedModules = 0;
	
	for(u32 phIndex = 0; phIndex < header->e_phnum; phIndex++)
	{
		Elf32_Phdr* ph = (Elf32_Phdr*)(elf + header->e_phoff + phIndex * header->e_phentsize);
		if(ph->p_type == PT_LOAD && ph->p_vaddr != 0 && ph->p_filesz ==0)
		{
			if(skipedModules == moduleToSkip)
				return phIndex;

			//we register the end of a module (ie a BSS)
			skipedModules++;			
		}
	}
	
	throw Exception("No bss segment found!" , -1);
}

u32 PluginPatch::FindSegmentSize(u8* elf, u32 segmentIndex) const
{
	Elf32_Ehdr* header = (Elf32_Ehdr*)elf;
	Elf32_Phdr* pheader = (Elf32_Phdr*)(elf + header->e_phoff + segmentIndex * header->e_phentsize);

	return pheader->p_filesz;
}

u64 PluginPatch::GetElfSize(const u8* elf) const
{
	Elf32_Ehdr* header = (Elf32_Ehdr*)elf;
	u64 elfSize = header->e_ehsize;
	
	//we don' add the PHdr table size because the section is referenced
	//in the PHeaders (type = PT_PHDR)
	for(u32 phIndex = 0; phIndex < header->e_phnum; phIndex++)
	{
		Elf32_Phdr* ph = (Elf32_Phdr*)(elf + header->e_phoff + phIndex * header->e_phentsize);
		//we ignore the PT_LOAD associated to the PHT
		if(ph->p_type == PT_LOAD &&  ph->p_offset == header->e_phoff)
		  continue;
		elfSize += ph->p_filesz;
	}
	
	return elfSize;
}

void PluginPatch::Plug(u32 segmentIndex, u32 bssSegmentIndex, u8* source, u8* dest) const
{
	Elf32_Ehdr* inHeader = (Elf32_Ehdr*)source;
	Elf32_Ehdr* outHeader = (Elf32_Ehdr*)dest;

	Elf32_Off outPos = 0;

	//copy of elf header
	memcpy(dest, source, inHeader->e_ehsize);
	outPos += inHeader->e_ehsize;

	//copy of pht
	memcpy(dest + outPos, source + inHeader->e_phoff, inHeader->e_phnum * inHeader->e_phentsize);
	outHeader->e_phoff = outPos;
	outPos += inHeader->e_phnum * inHeader->e_phentsize;

	//copy of each sections, except the pht again
	for(Elf32_Half phIndex = 0; phIndex < inHeader->e_phnum; phIndex++)
	{
		Elf32_Phdr* pHeader = (Elf32_Phdr*)(dest + outHeader->e_phoff + phIndex * outHeader->e_phentsize);

		if(pHeader->p_type == PT_PHDR)
		{
			pHeader->p_offset = outHeader->e_phoff;
			continue;
		}
		//if the header is redifined as PT_LOAD
		else if(pHeader->p_type == PT_LOAD && pHeader->p_offset == inHeader->e_phoff)
		{
			pHeader->p_offset = inHeader->e_phoff;
			continue;
		}
		else if(pHeader->p_type == PT_LOAD && phIndex == bssSegmentIndex)
		{
			pHeader->p_offset = outPos;
			pHeader->p_memsz = _bssNewSize;
			continue;
		}
		else if(pHeader->p_type == PT_LOAD && phIndex == segmentIndex)
		{
			memcpy(dest + outPos, source + pHeader->p_offset, pHeader->p_filesz);
			memcpy(dest + outPos + _offset, _plugin.Content(), _plugin.Length());
			pHeader->p_offset = outPos;
			pHeader->p_filesz = _offset + _plugin.Length();
			pHeader->p_memsz = pHeader->p_filesz;
		}
		else
		{
			memcpy(dest + outPos, source + pHeader->p_offset, pHeader->p_filesz);
			pHeader->p_offset = outPos;
		}

		outPos += pHeader->p_filesz;
	}
}

void PluginPatch::Plug(u32 segmentIndex, u8* source, u8* dest) const
{
	Elf32_Ehdr* inHeader = (Elf32_Ehdr*)source;
	Elf32_Ehdr* outHeader = (Elf32_Ehdr*)dest;
	Elf32_Off outPos = 0;
	bool newSegment = (segmentIndex == 0);

	//copy of elf header
	memcpy(dest, source, inHeader->e_ehsize);
	outPos += inHeader->e_ehsize;

	//copy of pht
	memcpy(dest + outPos, source + inHeader->e_phoff, inHeader->e_phnum * inHeader->e_phentsize);
	outHeader->e_phoff = outPos;
	outPos += inHeader->e_phnum * inHeader->e_phentsize;
	
	//create a new header
	if(newSegment)
	{
		memcpy(dest + outPos, _newProgramSection, sizeof(Elf32_Phdr));
		outHeader->e_phnum = inHeader->e_phnum +1;
		outPos += sizeof(Elf32_Phdr);
		//set the segmentIndex to the created section
		segmentIndex = outHeader->e_phnum - 1;
	}

	//copy of each sections, except the pht again
	for(Elf32_Half phIndex = 0; phIndex < inHeader->e_phnum; phIndex++)
	{
		Elf32_Phdr* pHeader = (Elf32_Phdr*)(dest + outHeader->e_phoff + phIndex * outHeader->e_phentsize);

		if(pHeader->p_type == PT_PHDR)
		{
			pHeader->p_offset = outHeader->e_phoff;
			continue;
		}
		//if the header is redifined as PT_LOAD
		else if(pHeader->p_type == PT_LOAD && pHeader->p_offset == inHeader->e_phoff)
		{
			//if new segment, we add 20 to the header table size
			if(newSegment)
			{
				pHeader->p_filesz = pHeader->p_filesz + 0x20;
				pHeader->p_memsz = pHeader->p_filesz;
			}
			pHeader->p_offset = outHeader->e_phoff;
			continue;
		}
		else if(phIndex == segmentIndex)
		{
			*pHeader = *_newProgramSection;
			pHeader->p_offset = outPos;
			pHeader->p_filesz = _plugin.Length();
			pHeader->p_memsz = pHeader->p_filesz;
			
			memcpy(dest + outPos, _plugin.Content(), pHeader->p_filesz);
		}
		else
		{
			memcpy(dest + outPos, source + pHeader->p_offset, pHeader->p_filesz);
			pHeader->p_offset = outPos;
		}

		outPos += pHeader->p_filesz;
	}
}

u32 PluginPatch::Patching(TitleEventArgs &processControl) const
{
  //apply cmd handles
  for(vector<SimplePatch>::const_iterator ite = _commandHandles.begin(); ite != _commandHandles.end(); ite++)
		ite->ApplyPatch(processControl);

  u8* sourceElf = (u8*)processControl.buffer.Content();
  ArmHeader* arm = NULL;
  u32 armLength = 0;
  
  if(!IsElf(sourceElf))
  {
	  arm = (ArmHeader*)sourceElf;
	  armLength = arm->headerSize + arm->offset;
	  sourceElf = sourceElf + armLength;
	  if(arm->headerSize != sizeof(ArmHeader) || !IsElf(sourceElf))
		  throw Exception("The module isn't arm nor elf", -1);
  }

  u32 modulesToSkip = FindIOSVersionIndex(processControl.buffer);
  u32 bssSegment = FindBssSegment(sourceElf, modulesToSkip);
  u32 plugedSegment = _replaceSection;
  u64 newElfLength = GetElfSize(sourceElf);
  
  if(!_newProgramSection)
	plugedSegment = FindPlugedSegment(sourceElf, modulesToSkip);
	
  //if replace section = 0 and newHeader  != NULL, we create a new section
  if(_newProgramSection && _replaceSection == 0)
	newElfLength += sizeof(Elf32_Phdr);
  else
	newElfLength += (_offset - FindSegmentSize(sourceElf, plugedSegment));
	
  newElfLength += _plugin.Length();
	
  if(arm)
	  arm->size = newElfLength;

  u8* destElf = (u8*)malloc(TITLE_ROUND_UP(newElfLength + armLength, 64));
  if(!destElf)
    throw Exception("Not enough memory!", -1);
	
  try
  {
	memset(destElf, 0 , TITLE_ROUND_UP(newElfLength + armLength, 64));
	if(arm)
		memcpy(destElf, arm, armLength);
	
	if(!_newProgramSection)
	  Plug(plugedSegment, bssSegment, sourceElf, destElf + armLength);
	else
	  Plug(plugedSegment, sourceElf, destElf + armLength);
  }
  catch(Exception &ex)
  {
	free(destElf);
	throw;
  }
  catch(...)
  {
	free(destElf);
	throw;
  }
  
  processControl.buffer.Clear();
  processControl.buffer.Append(destElf, TITLE_ROUND_UP(newElfLength + armLength, 64));
  processControl.tmdInfo->size = TITLE_ROUND_UP(newElfLength + armLength, 64);
  free(destElf);
  
  return 1;
}
