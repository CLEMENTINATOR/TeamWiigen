#ifndef _TITLE_H_
#define _TITLE_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include "../Object.h"
#include "event/TitleEvent.h"
#include "event/TitleEventArgs.h"
#include "security/Identification.h"

#define TITLE_BLOCK_SIZE 1000

#define TITLE_ROUND_UP(x,n)	(-(-(x) & -(n)))
#define TITLE_ROUND_DOWN(x,n) ((x) & ~((n) - 1))

#define INIT_PROCESS_CONTROL(p, s) p.tmdInfo = s;\
		p.skipStep = false;\
		p.abortProcess = false;

/*!
 * \namespace Libwiisys::System
 * \brief Provides base items to manipulate the NAND
 */

namespace Libwiisys {namespace System {

		/**
		 * \class Title
		 * \brief This class allow all the Title utilisation.
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */

		/**
		 *@brief Return the title id
		 *@param title The 16hex digit representation of the title
		 *@return The title id
		 */
		inline u32 TITLE_ID(u64 title) {return (u32)title;}

		/**
		 *@brief Return the title type
		 *@param title The 16hex digit representation of the title
		 *@return The title type
		 */
		inline u32 TITLE_TYPE(u64 title) {return title >> 32;}

		/**
		 *@brief Return if the title is an ios
		 *@param title The 16hex digit representation of the title
		 *@return true if the title is an ios
		 */
		inline bool IS_IOS(u64 title) {return (title & 0x100000000ULL) > 0;}

		class Title : public Object
		{
		protected:

			/** Title key of the title used to encrypt/decrypt contents   */
			u8 _titleKey[16];

			/*!
			 * \brief Throw the TicketInstalling event
			 * \param processControl The argument of the event
			 */
			virtual void OnTicketInstalling(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TicketInstalled event
			 * \param processControl The argument of the event
			 */
			virtual void OnTicketInstalled(System::Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TmdInstalling event
			 * \param processControl The argument of the event
			 */
			virtual void OnTmdInstalling(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TmdInstalled event
			 * \param processControl The argument of the event
			 */
			virtual void OnTmdInstalled(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the ContentInstalling event
			 * \param processControl The argument of the event
			 */
			virtual void OnContentInstalling(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the ContentInstalled event
			 * \param processControl The argument of the event
			 */
			virtual void OnContentInstalled(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TicketLoading event
			 * \param processControl The argument of the event
			 */
			virtual void OnTicketLoading(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TicketLoaded event
			 * \param processControl The argument of the event
			 */
			virtual void OnTicketLoaded(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TmdLoading event
			 * \param processControl The argument of the event
			 */
			virtual void OnTmdLoading(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the TmdLoaded event
			 * \param processControl The argument of the event
			 */
			virtual void OnTmdLoaded(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the ContentLoading event
			 * \param processControl The argument of the event
			 */
			virtual void OnContentLoading(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Throw the ContentLoaded event
			 * \param processControl The argument of the event
			 */
			virtual void OnContentLoaded(Event::TitleEventArgs &processControl);

			/*!
			 * \brief Set the ticket of the title
			 * The ticket is saved in a "cetk" file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \param buffer The ticket buffer
			 */
			void Ticket(const Buffer& buffer);

			/*!
			 * \brief Get the ticket of the title
			 * The ticket is load from a "cetk" file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \return The Ticket buffer
			 */
			Buffer Ticket();

			/*!
			 * \brief Set the Tmd of the title
			 * The Tmd is saved in a "tmd" file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \param buffer The Tmd buffer
			 */
			void Tmd(const Buffer& buffer);

			/*!
			 * \brief Get the Tmd of the title
			 * The Tmd is load from a "tmd" file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \return The Tmd buffer
			 */
			Buffer Tmd();

			/*!
			 * \brief Set the Certificate of the title
			 * The Certificate is saved in a "cert" file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \param buffer The Certificate buffer
			 */
			void Certificate(const Buffer& buffer);

			/*!
			 * \brief Get the Certificate of the title
			 * The Certificate is load from a "cert" file. This file is save under the temporary directory
			 * If the file doesn't exists, it returns the wii Certificate.
			 * \see CreateTempDirectory
			 * \return The Certificate buffer.
			 */
			Buffer Certificate();

			/*!
			 * \brief Set the Crl of the title
			 * The Crl is saved in a "cert" file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \param buffer The Crl buffer
			 */
			void Crl(const Buffer& buffer);

			/*!
			 * \brief Get the Crl of the title
			 * The Crl is load from a "crl" file. This file is save under the temporary directory
			 * Generally, this is not used. we found that only in some wads.
			 * \see CreateTempDirectory
			 * \return The Crl buffer
			 */
			Buffer Crl();

			/*!
			 * \brief Set a Content of the title
			 * The Content is saved in a contentId file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \param buffer The Content buffer
			 * \param id The contentId of the Content
			 */
			void AddContent(const Buffer& buffer, u32 id);

			/*!
			 * \brief Get a Content of the title
			 * The Content is load from a contentId file. This file is save under the temporary directory
			 * \see CreateTempDirectory
			 * \param id The content id
			 * \return  The Content buffer
			 */
			Buffer GetContent(u32 id);

			/**
			 * \brief Encrypt content specified by the tmd_content
			 * \param b The decrypted content buffer
			 * \param tmdInfo The tmd_content associated to the content
			 **/
			void EncryptContent(Buffer& b,tmd_content* tmdInfo);

			/**
			 * \brief Decrypt content specified by the tmd_content
			 * \param b The encrypted content buffer
			 * \param tmdInfo The tmd_content associated to the content
			 **/
			void DecryptContent(Buffer& b,tmd_content* tmdInfo);

			/**
			 * \brief Decrypt the title key
			 * \param b_tik The cetk Buffer
			 */
			virtual void DecryptTitleKey(Buffer& b_tik);

			/**
			 * \brief Gets the shared1 content associated to the tmd_content
			 * \param c the tmd_content you need to get from shared1
			 * \return A buffer containing the shared1 content
			 **/
			Buffer GetSharedContent(tmd_content* c);

		public:

			/**
			 * \brief Reload IOS(secure fct : shutdown device, shutdown internet,shutdown logs..)
			 * \param ios The ios to be reloaded
			 */
			static void ReloadIOS(u32 ios);

			/**
			 * \brief get the actual running ios
			 * \return The ios number
			 */
			static u32 GetRunningIOS();

			/**
			 * \brief Save the decrypted title content
			 * The title needs to be loaded ( via nus, wad or nand)
			 * \param dirPath The dir we'll put the contents in
			 */
			void SaveDecryptedContent(const std::string& dirPath);

			/*!
			 * \brief Constructor
			 * \param automaticCleaning If true, temporary files will be automatically cleaned (true by default)
			 */
			Title(bool automaticCleaning = true);

			/*!
			 * \brief Load a title from a wad file
			 * All extracted files will be stored in a temp directory.
			 * \param file The full path of the wad
			 * \param tempFolder The folder where to store title elements. ("sd:/tmp" by default)
			 */
			void LoadFromWad(const std::string& file, const std::string& tempFolder = "sd:/tmp");

			/*!
			 * \brief Load a title from the nand
			 * You need to be under an ios that allow ES usage
			 * All extracted files will be stored in a temp directory.
			 * \param titleId The full id of the title (type + number)
			 * \param tempFolder The folder where to store title elements. ("sd:/tmp" by default)
			 */
			void LoadFromNand(u64 titleId, const std::string& tempFolder = "sd:/tmp");

			/*!
			 * \brief Load a title from the nus server
			 * You need to be under an ios that allow network connections.
			 * All downloaded files will be stored in a temp directory.
			 * \param titleId The full id of the title (type + number)
			 * \param revision The version of the title. 0 if you want the newest.
			 * \param tempFolder The folder where to store title elements. ("sd:/tmp" by default)
			 */
			void LoadFromNusServer(u64 titleId, u16 revision = 0, const std::string& tempFolder = "sd:/tmp");

			/**
			 * \brief Save the title as a wad file
			 * \param fileName The wad filepath
			 */
			void PackAsWad(const std::string& fileName);

			/*!
			 * \brief Get the list of all installed IOS
			 * \return A list of IOS number
			 */
			static std::vector<u8> GetInstalledIos();

			/*!
			 * \brief Gets the wad formated ( like NUSD) name
			 * \param tid The id of the title
			 * \param rev The version of the title
			 * \return The wad name
			 */
			static std::string GetWadFormatedName(u64 tid,u16 rev);

			/*!
			 * \brief Get the version of an installed title
			 * \param titleId The id of the title to get the installed version
			 * \return The title version
			 */
			static u16 GetInstalledTitleVersion(u64 titleId);

			/*!
			 * \brief Install the title
			 * You need to be under an ios with sufficient privileges.
			 * The title need to be loaded (from nus, wad or everything else).
			 */
			void Install();

			/*!
			 * \brief Uninstall the loaded title
			 */
			void Uninstall();

			/*!
			 * \brief Uninstall a specific title
			 * \param titleId The id of the title to uninstall
			 */
			static void Uninstall(u64 titleId);

			/*!
			 * \brief Check if the currently loaded title is installed
			 * \return True if the title is installed
			 */
			bool IsInstalled();

			/*!
			 * \brief Check if a title is installed
			 * It doesn't care of the title version
			 * \param titleId The title to check
			 * \return true if the title is installed
			 */
			static bool IsInstalled(u64 titleId);

			/*!
			 * \brief Clean all downloaded/extracted files.
			 */
			void Clean();

			/*!
			 * \brief Create all temporary folder
			 * The folder will be tempDirectory/titleId/revision
			 * \param titleId The id of the title to store
			 * \param revision The version of the title to store
			 * \param tempDirectory Location where to put files/directories
			 */
			void CreateTempDirectory(u64 titleId, u16 revision, const std::string& tempDirectory);

			/*!
			 * \brief Get the full temp directory associated to the title
			 * The temp directory is build with a base temp directory + the titleId and the revision
			 * \return the full temp directory
			 */
			std::string TempDirectory();

			/*!
			 * \brief Destructor
			 * If the title was constructed automaticCleaning to true,
			 * temp folder will be deleted
			 * \see Title
			 */
			virtual ~Title();

			//Events
			/**  Event associated to the OnTicketInstalling fct*/
			Event::TitleEvent TicketInstallingEvent;

			/**  Event associated to the OnTicketInstalled fct*/
			Event::TitleEvent TicketInstalledEvent;

			/**  Event associated to the OnTmdInstalling fct*/
			Event::TitleEvent TmdInstallingEvent;

			/**  Event associated to the OnTmdInstalled fct*/
			Event::TitleEvent TmdInstalledEvent;

			/**  Event associated to the OnContentInstalling fct*/
			Event::TitleEvent ContentInstallingEvent;

			/**  Event associated to the OnContentInstalled fct*/
			Event::TitleEvent ContentInstalledEvent;

			/**  Event associated to the OnTicketLoading fct*/
			Event::TitleEvent TicketLoadingEvent;

			/**  Event associated to the OnTicketLoaded fct*/
			Event::TitleEvent TicketLoadedEvent;

			/**  Event associated to the OnTmdLoading fct*/
			Event::TitleEvent TmdLoadingEvent;

			/**  Event associated to the OnTmdLoaded fct*/
			Event::TitleEvent TmdLoadedEvent;

			/**  Event associated to the OnContentLoading fct*/
			Event::TitleEvent ContentLoadingEvent;

			/**  Event associated to the OnContentLoaded fct*/
			Event::TitleEvent ContentLoadedEvent;
		private:
			u32 _tikLen;
			u32 _tmdLen;
			u64 _titleId;
			u16 _revision;
			u32 _dataLen;

			std::string _directory;
			bool automaticClean;
			bool canDeleteRootTempDirectory;

			/*!
			 * \brief Extract a title element.
			 * \param path The full path of the title elemnt
			 * \return A buffer containing the file Contents, or a null buffer if the path doesnt exists
			 */
			Buffer GetTitleElementFromTemp(const std::string &path);

			/*!
			 * \brief Uninstall a specific title deleting folder instead of using ES functions
			 * \param titleId The id of the title to uninstall
			 */
			static void UninstallUsingISFS(u64 titleId);
		};
	}
}
#endif
