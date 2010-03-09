Sciifii installer V2 based on cios corp v3.6
Made by Arasium, Teton and Fanta.
Tested by JeanMi59226, Jicay, crwys, Vlad and Thetataz (and many others)
Special thanks to Waninkoko for his help
Thanks to da_letter_a for the cios corp knowledge

Bugs: teamwiigen@googlemail.com

Requirements:
A SD Card (With at least 200mb of free space)
A way to launch homebrew on your wii (Bannerbomb,hbc,Twilight hack ect...)

What it does:
-Hack your wii ! (Light Mode) : Restore Trucha Bug, Install cIOS rev17b, Install Priiloader
-Hack your wii ! (Full Mode) : Restore Trucha Bug, Install cIOS rev17b, Install Priiloader, Install USB LoaderGX
-Advanced Menu (Lets you choose what to install, experts only)
-Unhack your wii. : Remove all cios and update you to 4.2

Allows you to install:
-Restore Trucha Bug
-Install cIOS rev17b
-Install cIOScorp   
-Install firmware 4.2
-Install Priiloader
-Install USB LoaderGX


Estimated Install Time :
						  On a 1MB/s connexion
						  Download     Install    
			Light   Mode:     2m10        1m40      
			Full    Mode:    26m20       11m00
			All Features:    34m44       20m05
			Unhack      :    25m43       11m30
			
Please, read the da_letter_a cioscorp readme for more informations on the cioscorp.

/*********************/
		PC Tool
/*********************/

Required: Framework.NET 3.5

If your wii do not have internet access, or if you want to download the needed elements very quicker
Use our Sciifii Offline File Downloader computer program and run it to have the files.
You need to put your sciifi configuration in the same folder of the downloader.
This tool allow you to select what you want from sciifii and will ask you for a destination folder.
It will create a folder named "sciifii" and put all the needed file into it (so the better choice is to
select the sd card when the app prompt you to choose a destination folder).
Just put them on sd:/sciifii and run Sciifii on your wii.

/*********************/
	Customisation
/*********************/

Sciifii is fully configurable. To modify sciifii, you just need to modify the config.xml.
We can view sciifi like a sequencer of steps. Each steps can switch on by one or more options.

for example:

<steps>
	<myStep options="toto|tata" />
</steps>

means that the step myStep can be switch on by enabling the option toto or tata.
So, of course, you need to define the options like that:

<options>
	<option name="toto" text="Waouh, sciifii is amazing :)" networkRequired="true" />
</options>

The name will be used as an identifier, the text will be displayed in the advanced menu
and networkRequired indicate if this option can be activated if the network isn't available.

The advanced menu is composed of the defined options (options are off by default).
To configure the basic menu, you need to define modes. Each mode will create an entry in the basic menu.

<modes>
	<mode text="Just do it" options="toto" flag="myFlag" />
</modes>

The text will be displayed in the menu. The options indicate wish options will be enabled if
the user choose this mode. And the flag allow you to put a flag 'on' in the configuration.
Actually, the only flag used is the 'Uninstall' (see the SystemUpdater step).

You can disable the AdvancedMode, modify the disclaimer and add an alert in the basic menu
modifying some the attributes MenuMessage, AllowAdvancedMode and the element Disclaimer.
The attribute workingDirectory indicate where sciifii need to research/put temp files (like wads)

/**********************/
	Availables steps
/**********************/

<IOSDowngrader option="TBR" id="15" revision="257" />
Downgrade the specified ios to the specified version

<IOSReloader option="TBR" id="15" user="0" fs="sd" />
reload under a specified ios.
user="0" and fs="sd" are required (this will be removed in a future version).

<TruchaRestorer option="TBR" id="36" revision="0" />
Install the specified ios (revision 0 means the latest one)
with the TBR patches

<TitleInstaller option="TBR" id="000000010000000f" revision="0" />
Just install a tile

<CiosInstaller option="cIOS" />
Install cios249 rev17b (DL patch)

<SystemUpdater option="update" />
Install the titles defined in system.

<Preloader option="Preloader" />
Install the preloader

<CorpInstaller option="corp" />
Launch the corp installation. Look at the corpItems to configure the corp.

<GXLoader option="GXLoader" />
Install the GXLoader

<WadBatchInstaller option="batch" folder="sd:/sciifii/batch" />	
Install all the wads found in the specified folder.