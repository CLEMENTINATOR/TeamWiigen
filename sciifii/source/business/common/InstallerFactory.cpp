#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwiisys/String/UtilString.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/system/Patching/SimplePatch.h>
#include <Libwiisys/system/Patching/TitlePatcher.h>

#include <sciifii/Config.h>
#include <sciifii/business/common/InstallerFactory.h>
#include <sciifii/business/common/KoreanKeyPatch.h>
#include <sciifii/business/Cios.h>
#include <sciifii/business/CompositeInstaller.h>
#include <sciifii/business/FileDownloader.h>
#include <sciifii/business/FileSystemTask.h>
#include <sciifii/business/Identifier.h>
#include <sciifii/business/MemoryPatcher.h>
#include <sciifii/business/Preloader.h>
#include <sciifii/business/TitleStep.h>
#include <sciifii/business/WadBatch.h>
#include <sciifii/business/StopSciifiiStep.h>
#include <sciifii/business/SystemStep.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::System::Patching;


Installer* InstallerFactory::Create(TiXmlElement* node)
{
  Installer* step(NULL);

  string nodeValue = UtilString::ToStr(node->Value());
  if(nodeValue == "SystemTask")
  {
    string message = UtilString::ToStr(node->Attribute("message"),"");
    string action = UtilString::ToStr(node->Attribute("action"),"");
    if (action != "reboot" && action != "exit")
         throw Exception("SystemStep action non existing");
         
    step = new SystemStep(action, message);     
  }
  else if(nodeValue == "Title")
  {
    u64 titleId = UtilString::ToU64(node->Attribute("id"),0, nr_hex);
    u16 revision = UtilString::ToU16(node->Attribute("revision"),0);
    string file = UtilString::ToStr(node->Attribute("wad"),"");
    string path = UtilString::ToStr(node->Attribute("path"),"");
    TitleAction action;
    string choice = UtilString::ToStr(node->Attribute("action"),"install");

	bool fakesignbool =  UtilString::ToBool(node->Attribute("fakesign"),false);
	Fakesign_Type fakesign;
	if(fakesignbool)
		fakesign = Fakesign_Force;
	else 
		fakesign = Fakesign_None;


    if(choice == "install")
      action = ti_Install;
    else if(choice == "uninstall")
      action = ti_Uninstall;
    else if (choice == "pack")
      action = ti_PackAsWad;
    else if (choice == "extract")
      action = ti_Extract;
    else if (choice == "decrypt")
      action = ti_Decrypt;
    else if (choice == "update")
      action = ti_Update;
    else
      throw Exception("Can't parse TitleAction enum from xml!");

    if (titleId!=0 && file=="")
      step= new TitleStep(titleId, revision, action, path,fakesign);
    else if (titleId==0 && file!="")
      step= new TitleStep(file, action, path,fakesign);
    else
      throw Exception("Title XML error");
  }
  else if(nodeValue == "CiosInstaller")
    step = CreateCios(node);
  else if(nodeValue == "MemoryPatcher")
  {
    step = new MemoryPatcher();

    TiXmlElement* patch = node->FirstChildElement();
    while (patch != NULL)
    {
      if (patch->Type() != TiXmlNode::TINYXML_COMMENT)
      {
        string nodeValue = UtilString::ToStr(patch->Value());
        if(nodeValue == "patch")
        {
          Buffer pattern;
          Buffer value;
          vector<string> splitPattern = UtilString::Split(UtilString::ToStr(patch->Attribute("pattern")),',');
          vector<string> splitValue = UtilString::Split(UtilString::ToStr(patch->Attribute("value")),',');

          for(u16 i = 0; i < splitPattern.size(); i++)
          {
            vector<string> val = UtilString::Split(splitPattern[i], 'x');
            if(val.size() != 2)
              throw Exception("Value length != 2");

            u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
            pattern.Append(&v, 1);
          }

          for(u16 i = 0; i < splitValue.size(); i++)
          {
            vector<string> val = UtilString::Split(splitValue[i], 'x');
            u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
            value.Append(&v, 1);
          }

          ((MemoryPatcher*)step)->AddPatch(((MemoryPatch)
                                            {
                                              pattern, value
                                            }
                                           ));
        }
        else
          throw Exception("Child node of MemoryPatcher not defined.");
      }
      patch = patch->NextSiblingElement();
    }
  }
  else if(nodeValue == "Identifier")
  {
    u16 user = UtilString::ToU16(node->Attribute("user"));
    step = new Identifier((UserType)user);
  }
  else if(nodeValue == "Preloader")
  {
    string file = UtilString::ToStr(node->Attribute("file"));
    if(file == "")
      throw Exception("Priiloader file must be provided.");


    step = new Preloader(file);
  }
  else if(nodeValue == "WadBatch")
  {
    string folder = UtilString::ToStr(node->Attribute("folder"));
    string saction = UtilString::ToStr(node->Attribute("action"),"install");
    TitleAction action;
    if(saction == "install")
      action = ti_Install;
    else if(saction == "uninstall")
      action = ti_Uninstall;
    else
      throw Exception("Can't parse WadBatchAction enum from xml!");

    step = new WadBatch(folder,action);
  }
  else if(nodeValue == "CompositeInstaller")
  {
    string name = UtilString::ToStr(node->Attribute("name"));
    
    step = new CompositeInstaller(name);
    FillCompositeInstaller(step, node);
  }
  else if(nodeValue == "FileDownloader")
  {
    string file = UtilString::ToStr(node->Attribute("file"));

    step = new FileDownloader(file);
  }
  else if(nodeValue == "FileSystem")
  {
    string target = UtilString::ToStr(node->Attribute("target"));
    string destination = UtilString::ToStr(node->Attribute("destination"), "");
    string saction = UtilString::ToStr(node->Attribute("action"));
    string stype = UtilString::ToStr(node->Attribute("type"));
    bool recursive = UtilString::ToBool(node->Attribute("recursive"), false);

    FSTType type = FSTType_File;
    FSTAction action = FSTAction_Move;

    if(stype == "file")
      ;
    else if(stype == "folder")
      type = FSTType_Folder;
    else
      throw Exception("Can't parse FSTType from \"" + stype + "\".");

    if(saction == "move")
      action = FSTAction_Move;
    else if(saction == "copy")
      action = FSTAction_Copy;
    else if(saction == "delete")
      action = FSTAction_Delete;
	else if(saction == "create")
      action = FSTAction_Create;

    step = new FileSystemTask(target, action, type, destination, recursive);
  }
	else if(nodeValue == "StopSciifii")
		step = new StopSciifiiStep();
  else
    throw Exception("This step doesn't exists");

  step->Options(UtilString::ToStr(node->Attribute("option"), ""));
  step->Region(UtilString::ToStr(node->Attribute("regions"), ""));
  step->IgnoredExceptions(UtilString::ToStr(node->Attribute("exceptions"), ""));

  return step;
}

Installer* InstallerFactory::CreateCios(TiXmlElement* node)
{
  u32 iosSource = UtilString::ToU32(node->Attribute("source"));
  u32 iosDest = UtilString::ToU32(node->Attribute("slot"), iosSource);

  u16 iosRevision = UtilString::ToU16(node->Attribute("revision"));
  s32 ciosRevision = UtilString::ToS32(node->Attribute("ciosRevision"), -1);

  bool del = UtilString::ToBool(node->Attribute("delete"), false);

  string banner = UtilString::ToStr(node->Attribute("banner"), "");
  
  Cios* step = new Cios(iosSource, iosRevision, iosDest, ciosRevision, banner, del);

  TiXmlElement* section = node->FirstChildElement();
  while (section != NULL)
  {
    if (section->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      string nodeValue = UtilString::ToStr(section->Value());
      if(nodeValue == "modules")
        FillCiosModules(step, section);
      else if(nodeValue=="patches")
        FillCiosPatches(step, section);
      else
        throw Exception("Child node of Cios not defined");
    }
    section=section->NextSiblingElement();
  }

  return step;
}

void InstallerFactory::FillCiosModules(Installer* cios, TiXmlElement* xml)
{
  TiXmlElement* module = xml->FirstChildElement();
  while (module != NULL)
  {
    if (module->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      if(UtilString::ToStr(module->Value()) != "module")
        throw Exception("There can only be module item in modules");

      string file = UtilString::ToStr(module->Attribute("file"));
      s32 position = UtilString::ToS32(module->Attribute("position"), -1);

      ((Cios*)cios)->AddModule((customModule)
                               {
                                 file, position
                               }
                              );
    }
    module = module->NextSiblingElement();
  }
}

void InstallerFactory::FillCiosPatches(Installer* cios, TiXmlElement* xml)
{
  TiXmlElement* child = xml->FirstChildElement();
  while (child != NULL)
  {
    if (child->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      string nodeValue = UtilString::ToStr(child->Value());
      if(nodeValue=="prebuild")
      {
        string patchName=UtilString::ToStr(child->Attribute("name"));
		if(patchName == "KoreanKey")
		{
			((Cios*)cios)->AddPatch(SimplePatch::KoreanKey_EnablePatch());
			((Cios*)cios)->AddPatch(new KoreanKeyPatch());
		}
		else
			((Cios*)cios)->AddPatch(new SimplePatch(*SimplePatch::getPatch(patchName)));
      }

      if(nodeValue=="SimplePatch")
      {
        string module=UtilString::ToStr(child->Attribute("module"),"");
        Buffer pattern;
        Buffer value;
        u32 offset = UtilString::ToU32(child->Attribute("offset"), -1, nr_hex);
        vector<string> splitPattern = UtilString::Split(UtilString::ToStr(child->Attribute("pattern")),',');
        vector<string> splitValue = UtilString::Split(UtilString::ToStr(child->Attribute("value")),',');

        for(u16 i = 0; i < splitPattern.size(); i++)
        {
          vector<string> val = UtilString::Split(splitPattern[i], 'x');
          if(val.size() != 2)
            throw Exception("Value length !=2");

          u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
          pattern.Append(&v, 1);
        }

        for(u16 i = 0; i < splitValue.size(); i++)
        {
          vector<string> val = UtilString::Split(splitValue[i], 'x');
          u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
          value.Append(&v, 1);
        }
        SimplePatch*s=new SimplePatch((u8*)pattern.Content(),(u8*)value.Content(),pattern.Length(),offset,module);
        ((Cios*)cios)->AddPatch(s);
      }

    }
    child = child->NextSiblingElement();
  }
}

void InstallerFactory::FillCompositeInstaller(Installer* composite, TiXmlElement* node)
{
  CompositeInstaller* step = (CompositeInstaller*)composite;

  TiXmlElement* child = node->FirstChildElement();

  while(child != NULL)
  {
    if (child->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      Installer* innerstep = InstallerFactory::Create(child);
      bool addToList = innerstep->Region().size() == 0;

      for(vector<u32>::iterator ite = innerstep->
                                      Region().begin();
          ite != innerstep->Region().end();
          ite++)
      {
        if(*ite == Config::GetRegion())
        {
          addToList = true;
          break;
        }
      }

      if(addToList)
        step->AddStep(innerstep);
      else
        delete innerstep;
    }

    child = child->NextSiblingElement();
  };
}
