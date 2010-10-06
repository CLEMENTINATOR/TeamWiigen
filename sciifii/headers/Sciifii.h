#ifndef _SCIIFII_GLOBAL_H_
#define _SCIIFII_GLOBAL_H_

//#define USE_ADVANCED_UI

#include <libwiisys.h>
#include <libwui.h>

#include "sciifii/Config.h"
#include "sciifii/Sciifii.h"
#include "sciifii/Tools.h"
#include "sciifii/Switch.h"
#include "sciifii/business/Cios.h"
#include "sciifii/business/CiosCorp.h"
#include "sciifii/business/CompositeInstaller.h"
#include "sciifii/business/FileDownloader.h"
#include "sciifii/business/FileSystemTask.h"
#include "sciifii/business/Identifier.h"
#include "sciifii/business/IosReloader.h"
#include "sciifii/business/MemoryPatcher.h"
#include "sciifii/business/Preloader.h"
#include "sciifii/business/TitleDowngrader.h"
#include "sciifii/business/TitleStep.h"
#include "sciifii/business/WadBatch.h"
#include "sciifii/business/common/FileManager.h"
#include "sciifii/business/common/Installer.h"
#include "sciifii/business/common/InstallerFactory.h"
#include "sciifii/business/common/KoreanKeyPatch.h"
#include "sciifii/business/common/ProgressEvent.h"
#include "sciifii/business/common/ProgressEventArgs.h"
#include "sciifii/ui/graphic/GraphicDisclaimer.h"
#include "sciifii/ui/text/MainMenu.h"
#include "sciifii/ui/text/AdvancedMenu.h"
#include "sciifii/ui/text/Disclaimer.h"
#include "sciifii/ui/text/VirtualPad.h"
#include "sciifii/ui/text/DynamicMenu.h"
#include "sciifii/ui/text/MenuManager.h"
#include "sciifii/ui/text/Events/NavigateEvent.h"
#include "sciifii/ui/text/Events/NavigateEventArgs.h"
#include "sciifii/ui/text/Events/SwitchEvent.h"
#include "sciifii/ui/text/Events/SwitchEventArgs.h"
#include "sciifii/ui/text/MenuItems/ExitMenuItem.h"
#include "sciifii/ui/text/MenuItems/MenuItem.h"
#include "sciifii/ui/text/MenuItems/ModeMenuItem.h"
#include "sciifii/ui/text/MenuItems/NavigationMenuItem.h"
#include "sciifii/ui/text/MenuItems/SeparatorMenuItem.h"
#include "sciifii/ui/text/MenuItems/StartMenuItem.h"
#include "sciifii/ui/text/MenuItems/SwitchMenuItem.h"
#include "sciifii/ui/text/MenuItems/MenuItemFactory.h"

#endif