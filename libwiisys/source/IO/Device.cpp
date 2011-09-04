/* SD and gecko headers */
#include <sdcard/gcsd.h>
#include <sdcard/wiisd_io.h>
#include <fat.h>
#include <Libwiisys/IO/Device.h>
#include <Libwiisys/IO/Path.h>
#include <Libwiisys/IO/usbstorage.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>


using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

static fatDevice devices[] = { { WII_ROOT_DIRECTORY, "Wii file system", NULL,0, false },
                               { "sd", "Wii SD Slot", &__io_wiisd, 0, false },
                               { "usb","USB Mass Storage Device", &__io_usbstorage, 0, false },
                               { "usb2","USB 2.0 Mass Storage Device", &__io_usb2storage, 0, false },
                               { "gca","SD Gecko (Slot A)", &__io_gcsda, 0, false },
                               { "gcb","SD Gecko (Slot B)", &__io_gcsdb, 0, false }, };

#define NB_DEVICES 6

void Device::EnsureShutdown()
{
  for (u16 deviceIndex = 0; deviceIndex < NB_DEVICES; deviceIndex++)
  {
    fatDevice *tempDevice = devices + deviceIndex;
    if (tempDevice->deviceHandles > 0)
      throw SystemException("Can shutdown device. Files are used.", tempDevice->deviceHandles);
  }

  for (u16 deviceIndex = 0; deviceIndex < NB_DEVICES; deviceIndex++)
  {
    fatDevice *tempDevice = devices + deviceIndex;

    if (tempDevice->interface != NULL && tempDevice->started)
	{
      tempDevice->interface->shutdown();
	  tempDevice->started = false;
	}
  }
}

string Device::GetWiiPath(const std::string &path)
{
  string rootPath = Path::GetRootName(path);
  return path.substr(rootPath.length() + 1);
}

bool Device::IsFatPath(const std::string &path)
{
  return Path::GetRootName(path) != WII_ROOT_DIRECTORY;
}

fatDevice& Device::FindDevice(const std::string &pathName)
{
  string mountName = Path::GetRootName(pathName);
  fatDevice *device = NULL;
  for (u32 deviceIndex = 0; deviceIndex < NB_DEVICES; deviceIndex++)
  {
    fatDevice *tempDevice = devices + deviceIndex;
    if (tempDevice->mount == mountName)
    {
      device = tempDevice;
      break;
    }
  }

  if (device == NULL)
    throw Exception("Device not found." + mountName);

  return *device;
}

void Device::Mount(const std::string &path)
{
  fatDevice& device = FindDevice(path);
  /* if not already mounted */
  if (device.deviceHandles == 0)
  {
    //Si ISFS
    if (device.interface == NULL)
      Mount();
    //Si device externe
    else
      Mount(device);
  }

  device.deviceHandles++;
}

void Device::Mount()
{
  s32 ret;

  ret = ISFS_Initialize();
  if (ret < 0)
    throw SystemException("Could not initialize NAND subsystem!", ret);
}

void Device::Mount(fatDevice &device)
{
  /* Initialize interface */
  if (!device.started)
  {
    device.interface->startup();
    device.started = true;
  }

  /* Mount device */
  s32 ret = fatMountSimple(device.mount.c_str(), device.interface);
  if (!ret)
    throw SystemException("Error mounting device!", ret);
}

void Device::UnMount(const std::string &path)
{
  fatDevice& device = FindDevice(path);

  if (device.deviceHandles == 0)
    return;

  device.deviceHandles--;

  /* if there is other handles, we don't unmount the device */
  if (device.deviceHandles != 0)
    return;

  //Si ISFS
  if (device.interface == NULL)
    UnMount();
  //Si device externe
  else
    UnMount(device);
}

void Device::UnMount()
{
  ISFS_Deinitialize();
}

void Device::UnMount(fatDevice &device)
{
  string devicePath = device.mount + ":/";
  /* Unmount device */
  fatUnmount(devicePath.c_str());
}

vector<string> Device::GetAvailableRoots()
{
  vector < string > availableDevices;

  for (u16 deviceIndex = 0; deviceIndex < NB_DEVICES; deviceIndex++)
  {
    try
    {
      string devicePath = devices[deviceIndex].mount + ":/";
      Device::Mount(devicePath);
      Device::UnMount(devicePath);
      availableDevices.push_back(devicePath);
    }
    catch (Exception &ex)
    {}
  }

  return availableDevices;
}


std::string Device::GetType()
{
  return "Libwiisys::IO::Device,"+Object::GetType();
}
