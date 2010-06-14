/* SD and gecko headers */
#include <sdcard/gcsd.h>
#include <sdcard/wiisd_io.h>
#include <fs/usbstorage.h>
#include <exception/Exception.h>
#include <fs/Directory.h>

#include <fs/Device.h>
#include <fs/Path.h>

using namespace std;

static fatDevice devices[] = {
	{ WII_ROOT_DIRECTORY,	"Wii file system",		NULL,		0 },
	{ "sd",		"Wii SD Slot",			&__io_wiisd, 0 },
	{ "usb",	"USB Mass Storage Device",	&__io_usbstorage, 0 },
	/*{ "usb2",	"USB 2.0 Mass Storage Device",	&__io_usb2storage, 0 },*/
	{ "gca",	"SD Gecko (Slot A)",		&__io_gcsda, 0 },
	{ "gcb",	"SD Gecko (Slot B)",		&__io_gcsdb, 0 },
};

#define NB_DEVICES 5
/**
*\brief Constructor
*/
Device::Device()
  : _started(false)
{}

/**
*\brief Returns the current static device instance
*\return The instance of class Device
*/
Device& Device::Instance()
{
	static Device d;
	return d;
}

/**
*\brief Startup all devices
*/
void Device::Startup()
{
	Device &d = Instance();
	if(!d._started)
	{
		for(u16 deviceIndex =0; deviceIndex < NB_DEVICES; deviceIndex++)
		{
			fatDevice *tempDevice = devices + deviceIndex;
			if(tempDevice->interface != NULL)
				tempDevice->interface->startup();
		}

		d._started = true;
	}
}

/**
*\brief Shutdown all devices
*/
void Device::EnsureShutdown()
{
	Device &d = Instance();
	if(d._started)
	{
		for(u16 deviceIndex =0; deviceIndex < NB_DEVICES; deviceIndex++)
		{
			fatDevice *tempDevice = devices + deviceIndex;
			if(tempDevice->deviceHandles > 0)
				throw Exception("Can shutdown device. Files are used.", tempDevice->deviceHandles);
		}

		for(u16 deviceIndex =0; deviceIndex < NB_DEVICES; deviceIndex++)
		{
			fatDevice *tempDevice = devices + deviceIndex;
			if(tempDevice->interface != NULL)
				tempDevice->interface->shutdown();
		}

		d._started = false;
	}
}

/*!
 * \brief Return a path which is used by ISFS storage access fonctions
 * \param path A file path
 * \return path which can be used for ISFS
 */
string Device::GetWiiPath(const std::string &path)
{
	string rootPath = Path::GetRootName(path);
	return path.substr(rootPath.length() + 1);
}

/*!
 * \brief Return if the path is a fat path or nor
 * \param path A file path
 * \return true if the path isn't a nand path,else false
 */
bool Device::IsFatPath(const std::string &path)
{
	return Path::GetRootName(path) != WII_ROOT_DIRECTORY;
}

/**
*\brief Find the device associated to pathName
*\param pathName A path name
*\return The fatDevice associated with pathName, or NULL if unexistant
*/
fatDevice& Device::FindDevice(const std::string &pathName)
{
	string mountName = Path::GetRootName(pathName);
	fatDevice *device = NULL;
	for(u32 deviceIndex = 0; deviceIndex < NB_DEVICES; deviceIndex++)
	{
		fatDevice *tempDevice = devices + deviceIndex;
		if(tempDevice->mount == mountName)
		{
			device = tempDevice;
			break;
		}
	}

	if(device == NULL)
		throw Exception("Device not found."+ mountName,-1);

	return *device;
}

/*!
 * \brief Mount the device where the file path is on
 * \param path A file path
 */
void Device::Mount(const std::string &path)
{
	fatDevice& device = FindDevice(path);
	/* if not already mounted */
	if(device.deviceHandles == 0)
	{
		//Si ISFS
		if(device.interface == NULL)
			Mount();
		//Si device externe
		else
			Mount(device);
	}

	device.deviceHandles++;
}

/*!
 * \brief Mount ISFS storage (Nand)
 */
void Device::Mount()
{
	s32 ret;

	ret = ISFS_Initialize();
	if(ret < 0)
		throw Exception("Could not initialize NAND subsystem!",ret);
}

/*!
 * \brief Mount device
 * \param device The device to mount
 * \see fatDevice
 */
void Device::Mount(fatDevice &device)
{
	/* Initialize interface */
	Startup();

	/* Mount device */
	s32 ret = fatMountSimple(device.mount.c_str(), device.interface);
	if (!ret)
		throw Exception("Error mounting device!",ret);
}

/*!
 * \brief Unmount where the file path is on
 * \param path A file path
 */
void Device::UnMount(const std::string &path)
{
	fatDevice& device = FindDevice(path);

	if(device.deviceHandles == 0)
			return;

	device.deviceHandles--;

	/* if there is other handles, we don't unmount the device */
	if(device.deviceHandles != 0)
		return;

	//Si ISFS
	if(device.interface == NULL)
		UnMount();
	//Si device externe
	else
		UnMount(device);
}

/*!
 * \brief UnMount ISFS storage (Nand)
 */
void Device::UnMount()
{
	ISFS_Deinitialize();
}

/*!
 * \brief UnMount device
 * \param device The device to unmount
 * \see fatDevice
 */
void Device::UnMount(fatDevice &device)
{
	string devicePath = device.mount + ":";
	/* Unmount device */
	fatUnmount(devicePath.c_str());
}

/*!
 * \brief Get avilable roots on the wii
 * \return a string array with the roots
 */
vector<string> Device::GetAvailableRoots()
{
	vector<string> availableDevices;

	for(u16 deviceIndex =0; deviceIndex < NB_DEVICES; deviceIndex++)
	{
		try
		{
			string devicePath = devices[deviceIndex].mount + ":/";
			Device::Mount(devicePath);
			Device::UnMount(devicePath);
			availableDevices.push_back(devicePath);
		}
		catch(Exception &ex)
		{}
	}

	return availableDevices;
}
