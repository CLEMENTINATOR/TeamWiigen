#include <system/Title.h>

#include <malloc.h>
#include <string>
#include <sstream>
#include <ogcsys.h>

#include <exception/Exception.h>
#include <exception/AbortException.h>
#include <fs/Directory.h>
#include <fs/File.h>
#include <fs/Path.h>
#include <fs/Device.h>
#include <com/NusServer.h>
#include <system/Certificate.h>
#include <rijndael.h>
#include <sha1.h>
#include <fs/Path.h>
#include <iomanip>

using namespace std;

#define ISALIGNED(x) ((((u32)x)&0x1F)==0)

void Title::ReloadIOS(u32 ios)
{
	Device::EnsureShutdown();
	IOS_ReloadIOS(ios);
}

/*!
 * \brief Constructor
 * \param automaticCleaning If true, temporary files will be automatically cleaned (true by default)
 */
Title::Title(bool automaticCleaning)
  : _dataLen(0),
	automaticClean(automaticCleaning)
{}

/*!
 * \brief Set the ticket of the title
 * The ticket is saved in a "cetk" file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param buffer The ticket content
 * \param len The ticket length
 */
void Title::Ticket(const Buffer& buffer)
{
	string fileName = _directory + "/cetk";
	if(File::Exists(fileName)) File::Delete(fileName);
	File &f = File::Create(fileName);
	f.Write(buffer);
	f.Close();
	delete &f;
}

/*!
 * \brief Extract a title element.
 * \param path The full path of the title elemnt
 * \param len This is used as output. It will contain the ticket length or 0 if the file doesn't exist
 * \return The address of the buffer. NULL if the file doesn't exists
 */
Buffer Title::GetTitleElementFromTemp(const string &path)
{
	Buffer b;
	if(!File::Exists(path))
		return b;

	return File::ReadToEnd(path);
}

/*!
 * \brief Get the ticket of the title
 * The ticket is load from a "cetk" file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param len This is used as output. It will contain the ticket length or 0 if the ticket doesn't exist
 * \return The address of the ticket or NULL if it doesn't exist. It's your responsability to free it.
 */
Buffer Title::Ticket()
{
	string fileName = _directory + "/cetk";
	return GetTitleElementFromTemp(fileName);
}

/*!
 * \brief Set the Tmd of the title
 * The Tmd is saved in a "tmd" file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param buffer The Tmd content
 * \param len The Tmd length
 */
void Title::Tmd(const Buffer& buffer)
{
	string fileName = _directory + "/tmd";
	if(File::Exists(fileName)) File::Delete(fileName);
	File &f = File::Create(fileName);
	f.Write(buffer);
	f.Close();
	delete &f;
}

/*!
 * \brief Get the Tmd of the title
 * The Tmd is load from a "tmd" file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param len This is used as output. It will contain the Tmd length or 0 if the Tmd doesn't exist
 * \return The address of the Tmd or NULL if it doesn't exist. It's your responsability to free it.
 */
Buffer Title::Tmd()
{
	string fileName = _directory + "/tmd";
	return GetTitleElementFromTemp(fileName);
}

/*!
 * \brief Set the Certificate of the title
 * The Certificate is saved in a "cert" file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param buffer The Certificate content
 * \param len The Certificate length
 */
void Title::Certificate(const Buffer& buffer)
{
	string fileName = _directory + "/cert";
	if(File::Exists(fileName)) File::Delete(fileName);
	File &f = File::Create(fileName);
	f.Write(buffer);
	f.Close();
	delete &f;
}

/*!
 * \brief Get the Certificate of the title
 * The Certificate is load from a "cert" file. This file is save under the temporary directory
 * If the file doesn't exists, it returns the wii Certificate.
 * \see CreateTempDirectory
 * \param len This is used as output. It will contain the Certificate length.
 * \return The address of the Certificate or NULL if it doesn't exist. It's your responsability to free it.
 */
Buffer Title::Certificate()
{
	string fileName = _directory + "/cert";

	if(!File::Exists(fileName))
	{
		Buffer b(Certificate::GetContent(), Certificate::GetLength());
		return b;
	}

	return GetTitleElementFromTemp(fileName);
}

/*!
 * \brief Set the Crl of the title
 * The Crl is saved in a "cert" file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param buffer The Crl content
 * \param len The Crl length
 */
void Title::Crl(const Buffer& buffer)
{
	string fileName = _directory + "/crl";
	if(File::Exists(fileName)) File::Delete(fileName);
	File &f = File::Create(fileName);
	f.Write(buffer);
	f.Close();
	delete &f;
}

/*!
 * \brief Get the Crl of the title
 * The Crl is load from a "crl" file. This file is save under the temporary directory
 * Generally, this is not used. we found that only in some wads.
 * \see CreateTempDirectory
 * \param len This is used as output. It will contain the Crl length.
 * \return The address of the Crl or NULL if it doesn't exist. It's your responsability to free it.
 */
Buffer Title::Crl()
{
	string fileName = _directory + "/crl";
	return GetTitleElementFromTemp(fileName);
}

/*!
 * \brief Set a Content of the title
 * The Content is saved in a contentId file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param buffer The Content buffer
 * \param len The Content length
 * \param id The contentId of the Content
 */
void Title::AddContent(const Buffer& buffer, u32 id)
{
	stringstream fileName;
	fileName << _directory << "/" << id;
	File &f = File::Create(fileName.str());
	f.Write(buffer);
	f.Close();
	delete &f;
}

/*!
 * \brief Get a Content of the title
 * The Content is load from a contentId file. This file is save under the temporary directory
 * \see CreateTempDirectory
 * \param id The content id
 * \param len This is used as output. It will contain the Content length.
 * \return The address of theContent or NULL if it doesn't exist. It's your responsability to free it.
 */
Buffer Title::GetContent(u32 id)
{
	stringstream fileName;
	fileName << _directory << "/" << id;
	return GetTitleElementFromTemp(fileName.str());
}

/*!
 * \brief Load a title from the nus server
 * You need to be under an ios that allow network connections.
 * All downloaded files will be stored in a temp directory.
 * \param titleId The full id of the title (type + number)
 * \param revision The version of the title. 0 if you want the newest.
 * \param tempFolder The folder where to store title elements. ("sd:/tmp" by default)
 */
void Title::LoadFromNusServer(u64 titleId, u16 revision, const std::string& tempFolder)
{
	TitleEventArgs processControl;

	CreateTempDirectory(titleId, revision, tempFolder);

	try
	{
		// Obtain ticket
		NusServer cetkServer(titleId, "cetk");
		processControl.buffer = cetkServer.GetResponse();
		INIT_PROCESS_CONTROL(processControl, NULL);
		OnTicketLoading(processControl);
		if(!processControl.skipStep)
		{
			Ticket(processControl.buffer);
			INIT_PROCESS_CONTROL(processControl, NULL);
			OnTicketLoaded(processControl);
		}


		//obtain TMD
		stringstream tmdName;
		if(revision!=0) tmdName << "tmd." << revision;
		else tmdName<<"tmd";


		NusServer tmdServer(titleId, tmdName.str());
		processControl.buffer = tmdServer.GetResponse();
		INIT_PROCESS_CONTROL(processControl, NULL);
		OnTmdLoading(processControl);

		bool skipTmd = processControl.skipStep;
		Buffer b_tmd = processControl.buffer;
		tmd* tmd_data = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)b_tmd.Content());


		//Get contents
		for (u16 cnt = 0; cnt < tmd_data->num_contents; cnt++)
		{
			tmd_content *content = &tmd_data->contents[cnt];

			//Construct content fileName
			stringstream filename;
			filename << hex << setw(8) << setfill('0') << content->cid;

			//Download it from NUS
			NusServer contentServer(titleId, filename.str());
			processControl.buffer = contentServer.GetResponse();
			_dataLen += processControl.buffer.Length();

			INIT_PROCESS_CONTROL(processControl, content);

			OnContentLoading(processControl);
			if(!processControl.skipStep)
			{
				AddContent(processControl.buffer, content->cid);
				INIT_PROCESS_CONTROL(processControl, content);
				OnContentLoaded(processControl);
			}
		}

		if(!skipTmd)
		{
			Tmd(b_tmd);
			processControl.buffer = b_tmd;
			INIT_PROCESS_CONTROL(processControl, NULL);
			OnTmdLoaded(processControl);
		}
	}
	catch(AbortException &ex)
	{}
}

/*!
 * \brief Load a title from a wad file
 * All extracted files will be stored in a temp directory.
 * \param file The full path of the wad
 * \param tempFolder The folder where to store title elements. ("sd:/tmp" by default)
 */
void Title::LoadFromWad(const std::string& file, const std::string& tempFolder)
{
	if(!File::Exists(file))
		throw Exception("The wad file doesn't exists.", -1);

	TitleEventArgs processControl;

	//getting wadBuffer
	Buffer wadBuffer = File::ReadToEnd(file);

	try
	{
		wad_header *header =  (wad_header*)wadBuffer.Content();

		//getting offsets
		u32 o_cert = TITLE_ROUND_UP(header->header_len, 64);
		u32 o_crl = o_cert + TITLE_ROUND_UP(header->certs_len, 64);
		u32 o_tik = o_crl + TITLE_ROUND_UP(header->crl_len, 64);
		u32 o_tmd = o_tik + TITLE_ROUND_UP(header->tik_len, 64);
		u32 o_ctnt = o_tmd + TITLE_ROUND_UP(header->tmd_len, 64);

		//create temp directory
		Buffer p_tmd((char*)header + o_tmd, TITLE_ROUND_UP(header->tmd_len, 64));
		tmd* tmd_data = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)p_tmd.Content());
		CreateTempDirectory(tmd_data->title_id, tmd_data->title_version, tempFolder);

		// register certs and crl
		{
			Buffer b_cert((char*)header + o_cert, header->certs_len);
			Certificate(b_cert);
		}

		if(header->crl_len != 0)
		{
			Buffer b_crl((char*)header + o_crl, header->crl_len);
			Crl(b_crl);
		}

		//Getting Tiket
		processControl.buffer.Clear();
		processControl.buffer.Append((char*)header + o_tik, TITLE_ROUND_UP(header->tik_len, 64));
		INIT_PROCESS_CONTROL(processControl, NULL);
		OnTicketLoading(processControl);
		if(!processControl.skipStep)
		{
			Ticket(processControl.buffer);
			INIT_PROCESS_CONTROL(processControl, NULL);
			OnTicketLoaded(processControl);
		}

		//Getting tmd
		processControl.buffer = p_tmd;
		INIT_PROCESS_CONTROL(processControl, NULL);
		OnTmdLoading(processControl);
		bool skipTmd = processControl.skipStep;
		p_tmd = processControl.buffer;

		//we've reloaded the p_tmd
		//so we reload the tmd_data
		tmd_data = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)p_tmd.Content());

		//getting contents
		void* p_content = (char*)header + o_ctnt;
		for (u32 contentIndex = 0; contentIndex < tmd_data->num_contents; contentIndex++)
		{
			tmd_content &content = tmd_data->contents[contentIndex];
			u64 wadContentSize = content.size;

			processControl.buffer.Clear();
			processControl.buffer.Append(p_content, TITLE_ROUND_UP(content.size, 64));
			_dataLen += TITLE_ROUND_UP(content.size, 64);

			INIT_PROCESS_CONTROL(processControl, &content);
			OnContentLoading(processControl);
			if(!processControl.skipStep)
			{
				AddContent(processControl.buffer, content.cid);
				INIT_PROCESS_CONTROL(processControl, &content);
				OnContentLoaded(processControl);
			}

			p_content = (u8*)p_content + TITLE_ROUND_UP(wadContentSize, 64);
		}

		if(!skipTmd)
		{
			Tmd(p_tmd);
			processControl.buffer = p_tmd;
			INIT_PROCESS_CONTROL(processControl, NULL);
			OnTmdLoaded(processControl);
		}
	}
	catch(AbortException &ex)
	{	}
}

/*!
 * \brief Not implemented
 */
void Title::LoadFromNand(u64 titleId, const std::string& tempFolder)
{
	throw Exception("Title::LoadFromNand is not implemented.",-1);
}

/*!
 * \brief Save the title as a wad file
 */
void Title::PackAsWad(const string& fileName)
{
	Buffer b_tmd = Tmd();
	Buffer b_cert = Certificate();
	Buffer b_tik = Ticket();
	u8 pad = 0;

	/* Generating the wad header */
	wad_header header;

	header.header_len = 0x20;
	header.type[0] = 0x49;
	header.type[1] = 0x73; //"Is"
	header.padding = 0;
	header.certs_len = b_cert.Length();
	header.crl_len = 0;
	header.tik_len = 0x02A4;

	/* calulating the tmd and data_len */
	tmd* tmdData = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)b_tmd.Content());
	header.tmd_len = 484 + tmdData->num_contents * 36;
	b_tmd.Truncate(header.tmd_len);

	header.data_len = _dataLen;
	header.footer_len = 0;

	/* Creating the wad header Buffer */
	Buffer wadHeader(&header, sizeof(wad_header));

	/* filling the buffers to be 0x40 aligned */
	if(wadHeader.Length() % 64 != 0)
	{
		Buffer headerPadding(pad, 64 - wadHeader.Length() % 64);
		wadHeader.Append(headerPadding);
	}

	if(b_tmd.Length() % 64 != 0)
	{
		Buffer tmdPadding(pad, 64 - b_tmd.Length() % 64);
		b_tmd.Append(tmdPadding);
	}

	if(b_cert.Length() % 64 != 0)
	{
		Buffer certPadding(pad, 64 - b_cert.Length() % 64);
		b_cert.Append(certPadding);
	}

	//truncate to be sure that the ticket has the good length (due to nus)
	b_tik.Truncate(0x02A4ULL);
	if(b_tik.Length() % 64 != 0)
	{
		Buffer tikPadding(pad, 64 - b_tik.Length() % 64);
		b_tik.Append(tikPadding);
	}

	Directory::Create(Path::GetParentDirectory(fileName));
	File& wad = File::Create(fileName);

	try
	{
		wad.Write(wadHeader);
		wad.Write(b_cert);
		wad.Write(b_tik);
		wad.Write(b_tmd);

		tmdData = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)b_tmd.Content());
		for (u32 cnt = 0; cnt < tmdData->num_contents; cnt++)
		{
			tmd_content *tmdContent = &tmdData->contents[cnt];
			Buffer b_content = GetContent(tmdContent->cid);

			if(b_content.Length() % 64 != 0)
			{
				Buffer contentPadding(pad, 64 - b_content.Length() % 64);
				b_content.Append(contentPadding);
			}
			wad.Write(b_content);
		}

		wad.Close();
		delete &wad;
	}
	catch(Exception& ex)
	{
		wad.Close();
		delete &wad;
		throw;
	}
	catch(...)
	{
		wad.Close();
		delete &wad;
		throw;
	}
}

/*!
 * \brief Clean all downloaded/extracted files.
 */
void Title::Clean()
{
	// if already cleaned, we skip this
	if(_directory == "" || !Directory::Exists(_directory))
		return;

	Directory::Delete(_directory, true);
	string titleDir = Path::GetParentDirectory(_directory);
	if(Directory::IsEmpty(titleDir))
	{
		Directory::Delete(titleDir);
		string tempDirectory = Path::GetParentDirectory(titleDir);
		if(canDeleteRootTempDirectory && Directory::IsEmpty(tempDirectory))
			Directory::Delete(tempDirectory);
	}
}

/*!
 * \brief Install the title
 * You need to be under an ios with sufficient privileges.
 * The title need to be loaded (from nus, wad or everything else).
 */
void Title::Install()
{
	s32 ret;
	TitleEventArgs processControl;

	Buffer certificate = Certificate();
	Buffer crl = Crl();

	try
	{
		/* Install ticket */
		processControl.buffer = Ticket();
		INIT_PROCESS_CONTROL(processControl, NULL);
		OnTicketInstalling(processControl);
		if(!processControl.skipStep)
		{
			u32 ticketLen = SIGNED_TIK_SIZE((signed_blob*) processControl.buffer.Content());
			ret = ES_AddTicket((signed_blob*)processControl.buffer.Content(), ticketLen, (signed_blob*)certificate.Content(), certificate.Length(), (signed_blob*)crl.Content(), crl.Length());
			if(ret < 0)
				throw Exception("Error installing ticket.", ret);

			INIT_PROCESS_CONTROL(processControl, NULL);
			OnTicketInstalled(processControl);
		}

		//Install tmd
		processControl.buffer = Tmd();
		INIT_PROCESS_CONTROL(processControl, NULL);
		OnTmdInstalling(processControl);
		if(!processControl.skipStep)
		{
			u32 tmdLen = SIGNED_TMD_SIZE((signed_blob*)processControl.buffer.Content());
			ret = ES_AddTitleStart((signed_blob*)processControl.buffer.Content(), tmdLen, (signed_blob*)certificate.Content(), certificate.Length(), (signed_blob*)crl.Content(), crl.Length());
			if(ret < 0)
				throw Exception("Error starting title installation.", ret);

			INIT_PROCESS_CONTROL(processControl, NULL);
			OnTmdInstalled(processControl);
		}

		Buffer tmdBuffer = processControl.buffer;
		tmd* tmdData = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)tmdBuffer.Content());

		//Install contents
		for (u32 cnt = 0; cnt < tmdData->num_contents; cnt++)
		{
			tmd_content *tmdContent = &tmdData->contents[cnt];
			u32 cfd = 0;
			processControl.buffer = GetContent(tmdContent->cid);
			//Start content installation
			INIT_PROCESS_CONTROL(processControl, tmdContent);
			OnContentInstalling(processControl);
			if(!processControl.skipStep)
			{
				cfd = ES_AddContentStart(tmdData->title_id, tmdContent->cid);
				if (cfd < 0)
					throw Exception("Error adding content start.", ret);

				//writing content datas
				ret = ES_AddContentData(cfd, (u8*)processControl.buffer.Content(), processControl.buffer.Length());
				if (ret < 0)
				{
					//if an error occures, we ensure to close the content
					//and notify the system of the error
					ES_AddContentFinish(cfd);
					throw Exception("Error writing content.", ret);
				}

				//end content installation
				ret = ES_AddContentFinish(cfd);
				if (ret < 0)
					throw Exception("Error finising content installation.", ret);

				INIT_PROCESS_CONTROL(processControl, tmdContent);
				OnContentInstalled(processControl);
			}
		}

		ret = ES_AddTitleFinish();
		if (ret < 0)
			throw Exception("Error finising title installation", ret);
	}
	catch(AbortException &abort)
	{	}
	catch(Exception &ex)
	{
		//Cancel install
		ES_AddTitleCancel();

		throw;
	}
	catch(...)
	{
	    //Cancel install
		ES_AddTitleCancel();

		throw;
	}
}

/*!
 * \brief Uninstall the loaded title
 */
void Title::Uninstall()
{
	Buffer tmdBuffer = Tmd();

	tmd* tmdData = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)tmdBuffer.Content());
	Title::Uninstall(tmdData->title_id);
}

/*!
 * \brief Uninstall a specific title
 * \param titleId The id of the title to uninstall
 */
void Title::Uninstall(u64 titleId)
{
	tikview *viewData = NULL;
	u32 viewCnt;
	s32 ret;

	if((titleId & 0x100000000ULL) > 0ULL)
	{
		Title::UninstallUsingISFS(titleId);
		return;
	}

	ret = ES_GetNumTicketViews(titleId, &viewCnt);
	if(ret < 0)
		throw Exception("Error getting view count.", ret);

	viewData = (tikview *)memalign(32, sizeof(tikview) * viewCnt);
	if(!viewData)
		throw Exception("Not enough memory.", -1);

	try
	{
		ret = ES_GetTicketViews(titleId, viewData, viewCnt);
		if(ret < 0)
			throw Exception("Error getting ticket views.", ret);

		/* Delete all tickets */
		for (u32 tickViewIndex = 0; tickViewIndex < viewCnt; tickViewIndex++)
		{
			ret = ES_DeleteTicket(&viewData[tickViewIndex]);
			if(ret < 0)
				throw Exception("Error deleting title tickets.", ret);
		}

		// Delete title content
		ret = ES_DeleteTitleContent(titleId);
		if(ret < 0)
			throw Exception("Error deleting title contents.", ret);

		//delete title
		ret = ES_DeleteTitle(titleId);
		if(ret < 0)
			throw Exception("Error deleting title.", ret);
	}
	catch(...)
	{
		free(viewData);
		throw;
	}

	free(viewData);
}

/*!
 * \brief Uninstall a specific title deleting folder instead of using ES functions
 * \param titleId The id of the title to uninstall
 */
 void Title::UninstallUsingISFS(u64 titleId)
 {
	u32 titleType = titleId >> 32;
	u32 id = (u32)titleId;

	stringstream ticketPath;
	ticketPath << "wii:/ticket/" << setw(8) << setfill('0') << hex << titleType << setw(0) << "/" << setw(8) << id << setw(0) << ".tik";

	stringstream titlePath;
	titlePath << "wii:/title/" << setw(8) << setfill('0') << hex << titleType << setw(0) << "/" << setw(8) << id;


	File::Delete(ticketPath.str());
	Directory::Delete(titlePath.str(), true);
 }

/*!
 * \brief Get the list of all installed IOS
 * \return A list of IOS number
 */
vector<u8> Title::GetInstalledIos()
{
	vector<u8> ioses;
	u32 nbTitle;
	u64 *titlesBuffer = NULL;
	s32 ret;
	//Get stored IOS versions.
	ret = ES_GetNumTitles(&nbTitle);
	if(ret < 0)
		throw Exception("Error getting the number of installed titles.", ret);

	titlesBuffer = (u64*)memalign(32, sizeof(u64) * nbTitle);
	if(!titlesBuffer)
		throw Exception("Not enough memory.", -1);

	try
	{
		ret = ES_GetTitles(titlesBuffer, nbTitle);
		if(ret < 0)
			throw Exception("Error getting title list from nand.", ret);


		//filtering ios from other titles
		for(u32 titleIndex = 0; titleIndex < nbTitle; titleIndex++)
		{
			u32 type = *(u32*)(titlesBuffer + titleIndex);
			u32 number = (u32)titlesBuffer[titleIndex];

			//If IOS
			if(type == 1 && 2 < number && number < 0x100)
				ioses.push_back((u8)number);
		}
		free(titlesBuffer);
		titlesBuffer = NULL;
	}
	catch(...)
	{
		if(titlesBuffer)
			free(titlesBuffer);
		throw;
	}
	return ioses;
}

/*!
 * \brief Check if a title is installed
 * It doesn't care of the title version
 * \param titleId The title to check
 * \return true if the title is installed
 */
bool Title::IsInstalled(u64 titleId)
{
	u32 nbTitle;
	u64 *titlesBuffer = NULL;
	s32 ret;
	bool installed = false;

	//Get stored IOS versions.
	ret = ES_GetNumTitles(&nbTitle);
	if(ret < 0)
		throw Exception("Error getting the number of installed titles.", ret);

	titlesBuffer = (u64*)memalign(32, sizeof(u64) * nbTitle);
	if(!titlesBuffer)
		throw Exception("Not enough memory.", -1);

	try
	{
		ret = ES_GetTitles(titlesBuffer, nbTitle);
		if(ret < 0)
			throw Exception("Error getting title list from nand.", ret);

		//filtering ios from other titles
		for(u32 titleIndex = 0; titleIndex < nbTitle; titleIndex++)
			if(*(titlesBuffer + titleIndex) == titleId)
			{
				installed = true;
				break;
			}

		free(titlesBuffer);
		titlesBuffer = NULL;
	}
	catch(...)
	{
		if(titlesBuffer)
			free(titlesBuffer);
		throw;
	}

	return installed;
}

/*!
 * \brief Get the version of an installed title
 * \param titleId The id of the title to get the installed version
 * \return The title version
 */
u16 Title::GetInstalledTitleVersion(u64 titleId)
{
	u32 tmdLength;
	s32 ret;
	signed_blob* tmdBuffer = NULL;
	u16 titleVersion;

	/* Get TMD size */
	ret = ES_GetStoredTMDSize(titleId, &tmdLength);
	if (ret < 0)
		throw Exception("Error getting TMD length", ret);

	/* Allocate memory */
	tmdBuffer = (signed_blob*)memalign(32, TITLE_ROUND_UP(tmdLength, 32));
	if(!tmdBuffer)
		throw Exception("Not enough memory.", -1);

	/* Read TMD */
	ret = ES_GetStoredTMD(titleId, tmdBuffer, tmdLength);
	if(ret < 0)
	{
		free(tmdBuffer);
		throw Exception("Error getting stored tmd.", ret);
	}


	titleVersion = ((tmd *)SIGNATURE_PAYLOAD(tmdBuffer))->title_version;
	free(tmdBuffer);

	return titleVersion;
}

/*!
 * \brief Create all temporary folder
 * The folder will be tempDirectory/titleId/revision
 * \param titleId The id of the title to store
 * \param revision The version of the title to store
 * \param tempDirectory Location where to put files/directories
 */
void Title::CreateTempDirectory(u64 titleId, u16 revision, const std::string& tempDirectory)
{
	if(Path::GetRoot(tempDirectory) == tempDirectory || Directory::Exists(tempDirectory))
		canDeleteRootTempDirectory = false;
	else
		canDeleteRootTempDirectory = true;

	stringstream str;
	str << tempDirectory << "/" << hex << setw(8) << setfill('0') << TITLE_TYPE(titleId);
	str << setw(0) << "/" << setw(8) << TITLE_ID(titleId) << setw(0) << setfill(' ') << dec;
	if(revision>0)
		str << "v" << revision;

	_directory = str.str();
	_directory=Path::CleanPath(_directory);

	Directory::Create(_directory);
}

/*!
 * \brief Throw the TicketInstalling event
 * \param processControl The argument of the event
 */
void Title::OnTicketInstalling(TitleEventArgs &processControl)
{
	TicketInstallingEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TicketInstalled event
 * \param processControl The argument of the event
 */
void Title::OnTicketInstalled(TitleEventArgs &processControl)
{
	TicketInstalledEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TmdInstalling event
 * \param processControl The argument of the event
 */
void Title::OnTmdInstalling(TitleEventArgs &processControl)
{
	TmdInstallingEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TmdInstalled event
 * \param processControl The argument of the event
 */
void Title::OnTmdInstalled(TitleEventArgs &processControl)
{
	TmdInstalledEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the ContentInstalling event
 * \param processControl The argument of the event
 */
void Title::OnContentInstalling(TitleEventArgs &processControl)
{
	ContentInstallingEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the ContentInstalled event
 * \param processControl The argument of the event
 */
void Title::OnContentInstalled(TitleEventArgs &processControl)
{
	ContentInstalledEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TicketLoading event
 * \param processControl The argument of the event
 */
void Title::OnTicketLoading(TitleEventArgs &processControl)
{
	TicketLoadingEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TicketLoaded event
 * \param processControl The argument of the event
 */
void Title::OnTicketLoaded(TitleEventArgs &processControl)
{
	TicketLoadedEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TmdLoading event
 * \param processControl The argument of the event
 */
void Title::OnTmdLoading(TitleEventArgs &processControl)
{
	TmdLoadingEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the TmdLoaded event
 * \param processControl The argument of the event
 */
void Title::OnTmdLoaded(TitleEventArgs &processControl)
{
	TmdLoadedEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the ContentLoading event
 * \param processControl The argument of the event
 */
void Title::OnContentLoading(TitleEventArgs &processControl)
{
	ContentLoadingEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Throw the ContentLoaded event
 * \param processControl The argument of the event
 */
void Title::OnContentLoaded(TitleEventArgs &processControl)
{
	ContentLoadedEvent(this, &processControl);
	if(processControl.abortProcess)
		throw AbortException();
}

/*!
 * \brief Check if the currently loaded title is installed
 * \return True if the title is installed
 */
bool Title::IsInstalled()
{
	Buffer tmdBuffer = Tmd();

	tmd* tmdData = (tmd *)SIGNATURE_PAYLOAD((signed_blob*)tmdBuffer.Content());
	return Title::IsInstalled(tmdData->title_id);
}

/*!
 * \brief Destructor
 * If the title was constructed automaticCleaning to true,
 * temp folder will be deleted
 * \see Title
 */
Title::~Title()
{
	if(automaticClean)
		Clean();
}

/*!
 * \brief Get the full temp directory associated to the title
 * The temp directory is build with a base temp directory + the titleId and the revision
 * \return the full temp directory
 */
string Title::TempDirectory()
{
	return _directory;
}

string Title::GetWadFormatedName(u64 tid,u16 rev)
{
  stringstream wadName;
  u32 type= tid >> 32;
  u32 id = (u32)tid;
  if (type==1) // If IOS
  {
    wadName << "IOS" <<id;
	if(rev > 0)
		wadName << "-64-";
  }
  else
  {
    wadName << hex << setfill('0') << setw(8) << type << setw(0) << "-" << setw(8) << id << setw(0) << dec;
  }
  
  if (rev > 0) 
	wadName << "v" << rev;
	
  wadName<<".wad";

  return wadName.str();

}
