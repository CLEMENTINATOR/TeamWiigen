#ifndef LIBUTILS_H_
#define LIBUTILS_H_

/** \mainpage Libwiisys
 *
 * \section sec_intro Introduction
 *
 * libwiisys is a wii utils library for an more easy Wii system homebrew development. <br>
 * This library is written in C++, for all of the advantages it gives. <br>
 * This library was developed by team Wiigen ( Arasium,Teton & Fanta )
 *
 * \section sec_tools Needed tools/Libraries
 * To use liiwiisys, you need to have : <br>
 *  <a href="http://sourceforge.net/projects/devkitpro/"> Devkitpro </a> <br>
 *  <a href="http://sourceforge.net/projects/tinyxml/"> Tinyxml </a> <br>
 *
 *
 *
 *
 */


#ifdef __cplusplus

#include "Libwiisys/Buffer.h"
#include "Libwiisys/Event.h"
#include "Libwiisys/EventArgs.h"
#include "Libwiisys/Exceptions/AbortException.h"
#include "Libwiisys/Exceptions/Exception.h"
#include "Libwiisys/IO/Device.h"
#include "Libwiisys/IO/Directory.h"
#include "Libwiisys/IO/FatDirectory.h"
#include "Libwiisys/IO/FatFile.h"
#include "Libwiisys/IO/File.h"
#include "Libwiisys/IO/FileMode.h"
#include "Libwiisys/IO/NandDirectory.h"
#include "Libwiisys/IO/NandFile.h"
#include "Libwiisys/IO/Path.h"
#include "Libwiisys/IO/fatDevice.h"
#include "Libwiisys/IO/usbstorage.h"
#include "Libwiisys/Network/HttpRequest.h"
#include "Libwiisys/Network/NetworkUtility.h"
#include "Libwiisys/Network/NusServer.h"
#include "Libwiisys/Serialization/Xml.h"
#include "Libwiisys/Shell/Dol.h"
#include "Libwiisys/Shell/Elf.h"
#include "Libwiisys/Shell/dol_header.h"
#include "Libwiisys/Shell/elf_abi.h"
#include "Libwiisys/String/NumberRepresentation.h"
#include "Libwiisys/String/UtilString.h"
#include "Libwiisys/logging/FileLogger.h"
#include "Libwiisys/logging/GeckoLogger.h"
#include "Libwiisys/logging/ILogProvider.h"
#include "Libwiisys/logging/Log.h"
#include "Libwiisys/logging/LogStatus.h"
#include "Libwiisys/logging/LogType.h"
#include "Libwiisys/logging/WebLogger.h"
#include "Libwiisys/system/Title.h"
#include "Libwiisys/system/wadHeader.h"
#include "Libwiisys/system/Event/TitleEvent.h"
#include "Libwiisys/system/Event/TitleEventArgs.h"
#include "Libwiisys/system/Patching/ModulePatch.h"
#include "Libwiisys/system/Patching/Patch.h"
#include "Libwiisys/system/Patching/TitlePatcher.h"
#include "Libwiisys/system/Patching/PluginPatch.h"
#include "Libwiisys/system/Patching/SimplePatch.h"
#include "Libwiisys/system/Patching/TitleModule.h"
#include "Libwiisys/system/Security/Identification.h"
#include "Libwiisys/system/Security/UserType.h"
#include "Libwiisys/system/Security/Certificate.h"
#include "Libwiisys/threading/Thread.h"

#endif

#include "Libwiisys/rijndael.h"
#include "Libwiisys/sha1.h"

#endif /* LIBUTILS_H_ */
