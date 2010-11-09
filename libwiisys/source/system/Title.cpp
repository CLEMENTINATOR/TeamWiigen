#include <malloc.h>
#include <string>
#include <sstream>
#include <ogcsys.h>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <unistd.h>
#include <libwiisys/system/Title.h>
#include <libwiisys/sha1.h>
#include <libwiisys/rijndael.h>
#include <Libwiisys/Network/NusServer.h>
#include <Libwiisys/Network/NetworkUtility.h>
#include <Libwiisys/logging/Log.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Path.h>
#include <Libwiisys/IO/Device.h>
#include <Libwiisys/system/Security/Certificate.h>
#include <Libwiisys/system/wadHeader.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>
#include <Libwiisys/Exceptions/AbortException.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Network;
using namespace Libwiisys::Logging;
using namespace Libwiisys::IO;
using namespace Libwiisys::System;
using namespace Libwiisys::System::Event;
using namespace Libwiisys::System::Security;
using namespace Libwiisys::Exceptions;

#define ISALIGNED(x) ((((u32)x)&0x1F)==0)

static u32 _runningIos = 0;

Title::Title(bool automaticCleaning) :
    _dataLen(0), automaticClean(automaticCleaning)
{}

void Title::Ticket(const Buffer& buffer)
{
  string fileName = _directory + "/cetk";
  if (File::Exists(fileName))
    File::Delete(fileName);
  File &f = File::Create(fileName);
  f.Write(buffer);
  f.Close();
  delete &f;
}

Buffer Title::GetTitleElementFromTemp(const string &path)
{
  Buffer b;
  if (!File::Exists(path))
    return b;

  return File::ReadToEnd(path);
}

Buffer Title::Ticket()
{
  string fileName = _directory + "/cetk";
  return GetTitleElementFromTemp(fileName);
}

void Title::Tmd(const Buffer& buffer)
{
  string fileName = _directory + "/tmd";
  if (File::Exists(fileName))
    File::Delete(fileName);
  File &f = File::Create(fileName);
  f.Write(buffer);
  f.Close();
  delete &f;
}

Buffer Title::Tmd()
{
  string fileName = _directory + "/tmd";
  return GetTitleElementFromTemp(fileName);
}

void Title::Certificate(const Buffer& buffer)
{
  string fileName = _directory + "/cert";
  if (File::Exists(fileName))
    File::Delete(fileName);
  File &f = File::Create(fileName);
  f.Write(buffer);
  f.Close();
  delete &f;
}

Buffer Title::Certificate()
{
  string fileName = _directory + "/cert";

  if (!File::Exists(fileName))
  {
    Buffer b(Certificate::GetContent(), Certificate::GetLength());
    return b;
  }

  return GetTitleElementFromTemp(fileName);
}

void Title::Crl(const Buffer& buffer)
{
  string fileName = _directory + "/crl";
  if (File::Exists(fileName))
    File::Delete(fileName);
  File &f = File::Create(fileName);
  f.Write(buffer);
  f.Close();
  delete &f;
}

Buffer Title::Crl()
{
  string fileName = _directory + "/crl";
  return GetTitleElementFromTemp(fileName);
}

void Title::AddContent(const Buffer& buffer, u32 id)
{
  stringstream fileName;
  fileName << _directory << "/" << hex << setw(8) << setfill('0') << id
  << dec;
  File &f = File::Create(fileName.str());
  f.Write(buffer);
  f.Close();
  delete &f;
}

Buffer Title::GetContent(u32 id)
{
  stringstream fileName;
  fileName << _directory << "/" << hex << setw(8) << setfill('0') << id
  << dec;
  return GetTitleElementFromTemp(fileName.str());
}

void Title::LoadFromNusServer(u64 titleId, u16 revision,
                              const std::string& tempFolder)
{
  TitleEventArgs processControl;

  CreateTempDirectory(titleId, revision, tempFolder);
  _dataLen = 0;
  try
  {
    // Obtain ticket
    NusServer cetkServer(titleId, "cetk");
    processControl.buffer = cetkServer.GetResponse();
    DecryptTitleKey(processControl.buffer);
    INIT_PROCESS_CONTROL(processControl, NULL);
    OnTicketLoading(processControl);
    if (!processControl.skipStep)
    {
      Ticket(processControl.buffer);
      INIT_PROCESS_CONTROL(processControl, NULL);
      OnTicketLoaded(processControl);
    }

    //obtain TMD
    stringstream tmdName;
    if (revision != 0)
      tmdName << "tmd." << revision;
    else
      tmdName << "tmd";

    NusServer tmdServer(titleId, tmdName.str());
    processControl.buffer = tmdServer.GetResponse();
    INIT_PROCESS_CONTROL(processControl, NULL);
    OnTmdLoading(processControl);

    bool skipTmd = processControl.skipStep;
    Buffer b_tmd = processControl.buffer;
    tmd* tmd_data = (tmd *) SIGNATURE_PAYLOAD(
                      (signed_blob*) b_tmd.Content());

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
      if (!processControl.skipStep)
      {
        AddContent(processControl.buffer, content->cid);
        INIT_PROCESS_CONTROL(processControl, content);
        OnContentLoaded(processControl);
      }
    }

    if (!skipTmd)
    {
      Tmd(b_tmd);
      processControl.buffer = b_tmd;
      INIT_PROCESS_CONTROL(processControl, NULL);
      OnTmdLoaded(processControl);
    }
  }
  catch (AbortException &ex)
  {}
}

void Title::LoadFromNand(u64 titleId, const std::string& tempFolder)
{
  TitleEventArgs processControl;
  _directory = tempFolder;
  _dataLen = 0;
  stringstream ticketPath;
  stringstream contentPath;
  stringstream sharedPath;
  ticketPath << "wii:/ticket/" << setw(8) << setfill('0') << hex
  << TITLE_TYPE(titleId) << setw(0) << "/" << setw(8) << TITLE_ID(
    titleId) << setw(0) << ".tik";
  contentPath << "wii:/title/" << setw(8) << setfill('0') << hex
  << TITLE_TYPE(titleId) << setw(0) << "/" << setw(8) << TITLE_ID(
    titleId) << setw(0) << "/content/";
  sharedPath << "wii:/shared1/";

  /* Getting TMD from es */
  u32 tmd_size;
  u32 ret = ES_GetStoredTMDSize(titleId, &tmd_size);
  if (ret < 0)
    throw SystemException("Unable to get stored tmd size", ret);

  signed_blob *btmd = (signed_blob *) memalign(32, (tmd_size + 31) & (~31));
  if (btmd == NULL)
    throw Exception("Not enough memory");
  memset(btmd, 0, tmd_size);

  ret = ES_GetStoredTMD(titleId, btmd, tmd_size);
  if (ret < 0)
  {
    free(btmd);
    throw SystemException("Unable to get stored tmd", ret);
  }

  tmd *tmd_data = NULL;
  tmd_data = (tmd *) SIGNATURE_PAYLOAD(btmd);
  CreateTempDirectory(tmd_data->title_id, tmd_data->title_version, tempFolder); /* Creating temp docs */

  processControl.buffer = File::ReadToEnd(ticketPath.str()); /* cetk */
  processControl.buffer.Truncate(0x02A4ULL);
  DecryptTitleKey(processControl.buffer);

  INIT_PROCESS_CONTROL(processControl, NULL);
  OnTicketLoading(processControl);
  if (!processControl.skipStep)
  {
    Ticket(processControl.buffer);
    INIT_PROCESS_CONTROL(processControl, NULL);
    OnTicketLoaded(processControl);
  }

  Buffer b_tmd((void*) btmd, tmd_size); /* tmd  */
  processControl.buffer = b_tmd;
  INIT_PROCESS_CONTROL(processControl, NULL);
  OnTmdLoading(processControl);

  bool skipTmd = processControl.skipStep;
  b_tmd = processControl.buffer;

  tmd_data = (tmd *) SIGNATURE_PAYLOAD(btmd);

  for (u16 cnt = 0; cnt < tmd_data->num_contents; cnt++)
  {
    tmd_content *content = &tmd_data->contents[cnt];
    stringstream filename;
    if (content->type == 0x0001)
    {
      filename << contentPath.str() << hex << setw(8) << setfill('0')
      << content->cid << ".app";
      processControl.buffer = File::ReadToEnd(filename.str());
    }
    else if (content->type == 0x8001)
    {
      processControl.buffer = GetSharedContent(content);
    }
    else
    {
      free(btmd);
      throw Exception("Unknown content type !");
    }

    /* Content, on encrypte */

    EncryptContent(processControl.buffer, content);
    _dataLen += processControl.buffer.Length();
    INIT_PROCESS_CONTROL(processControl, content);
    OnContentLoading(processControl);
    if (!processControl.skipStep)
    {
      AddContent(processControl.buffer, content->cid);
      INIT_PROCESS_CONTROL(processControl, content);
      OnContentLoaded(processControl);
    }
  }

  if (!skipTmd)
  {
    Tmd(b_tmd);
    processControl.buffer = b_tmd;
    INIT_PROCESS_CONTROL(processControl, NULL);
    OnTmdLoaded(processControl);
  }
  free(btmd);
}

void Title::LoadFromWad(const std::string& file, const std::string& tempFolder)
{
  if (!File::Exists(file))
    throw Exception("The wad file doesn't exists : " + file);

  TitleEventArgs processControl;
  _dataLen = 0;
  //getting wadBuffer
  File& wadBuffer = File::Open(file, FileMode_Read);

  try
  {
    Buffer b_header;
    wadBuffer.Read(b_header, sizeof(wad_header));
    wad_header *header = (wad_header*) b_header.Content();

    //getting offsets
    u32 o_cert = TITLE_ROUND_UP(header->header_len, 64);
    u32 o_crl = o_cert + TITLE_ROUND_UP(header->certs_len, 64);
    u32 o_tik = o_crl + TITLE_ROUND_UP(header->crl_len, 64);
    u32 o_tmd = o_tik + TITLE_ROUND_UP(header->tik_len, 64);
    u32 o_ctnt = o_tmd + TITLE_ROUND_UP(header->tmd_len, 64);

    //create temp directory
    Buffer p_tmd;
    wadBuffer.Read(p_tmd, TITLE_ROUND_UP(header->tmd_len, 64), o_tmd);
    tmd* tmd_data = (tmd *) SIGNATURE_PAYLOAD((signed_blob*) p_tmd.Content());
    CreateTempDirectory(tmd_data->title_id, tmd_data->title_version, tempFolder);

    // register certs and crl
    {
      Buffer b_cert;
      wadBuffer.Read(b_cert, TITLE_ROUND_UP(header->certs_len, 64), o_cert);
      Certificate(b_cert);
    }

    if (header->crl_len != 0)
    {
      Buffer b_crl;
      wadBuffer.Read(b_crl, TITLE_ROUND_UP(header->crl_len, 64), o_crl);
      Crl(b_crl);
    }

    //Getting Tiket
    processControl.buffer.Clear();
    wadBuffer.Read(processControl.buffer, TITLE_ROUND_UP(header->tik_len, 64), o_tik);
    DecryptTitleKey(processControl.buffer);
    INIT_PROCESS_CONTROL(processControl, NULL);
    OnTicketLoading(processControl);
    if (!processControl.skipStep)
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
    tmd_data = (tmd *) SIGNATURE_PAYLOAD((signed_blob*) p_tmd.Content());

    //getting contents
    u32 contentOffset = o_ctnt;
    for (u32 contentIndex = 0; contentIndex < tmd_data->num_contents; contentIndex++)
    {
      tmd_content &content = tmd_data->contents[contentIndex];
      u64 wadContentSize = content.size;

      processControl.buffer.Clear();

      //this bullshit code has been done to handle crappy wads
      // for example the ios38v3867 from NUSD (because nusd doesn't
      // add padding data to the last content......)
      if((s32)contentIndex == (tmd_data->num_contents - 1))
      {
        u32 restToRead = wadBuffer.Size() - contentOffset;
        //use classic way if we can
        if(restToRead >= TITLE_ROUND_UP(content.size, 64))
        {
          wadBuffer.Read(processControl.buffer, TITLE_ROUND_UP(content.size, 64), contentOffset);
        }
        else
        {
          Buffer padding((u8)0, (u64)(TITLE_ROUND_UP(content.size, 64) - restToRead));
          wadBuffer.Read(processControl.buffer, restToRead, contentOffset);
          processControl.buffer.Append(padding);
        }
      }
      else
        wadBuffer.Read(processControl.buffer, TITLE_ROUND_UP(content.size, 64), contentOffset);

      _dataLen += TITLE_ROUND_UP(content.size, 64);

      INIT_PROCESS_CONTROL(processControl, &content);
      OnContentLoading(processControl);
      if (!processControl.skipStep)
      {
        AddContent(processControl.buffer, content.cid);
        INIT_PROCESS_CONTROL(processControl, &content);
        OnContentLoaded(processControl);
      }

      contentOffset += TITLE_ROUND_UP(wadContentSize, 64);
    }

    if (!skipTmd)
    {
      Tmd(p_tmd);
      processControl.buffer = p_tmd;
      INIT_PROCESS_CONTROL(processControl, NULL);
      OnTmdLoaded(processControl);
    }
  }
  catch (AbortException &ex)
  {}
  catch(Exception &ex)
  {
    wadBuffer.Close();
    delete &wadBuffer;
    throw;
  }
  catch(...)
  {
    wadBuffer.Close();
    delete &wadBuffer;
    throw;
  }

  wadBuffer.Close();
  delete &wadBuffer;
}

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
  tmd* tmdData = (tmd *) SIGNATURE_PAYLOAD((signed_blob*) b_tmd.Content());
  header.tmd_len = 484 + tmdData->num_contents * 36;
  b_tmd.Truncate(header.tmd_len);

  header.data_len = _dataLen;
  header.footer_len = 0;

  /* Creating the wad header Buffer */
  Buffer wadHeader(&header, sizeof(wad_header));

  /* filling the buffers to be 0x40 aligned */
  if (wadHeader.Length() % 64 != 0)
  {
    Buffer headerPadding(pad, 64 - wadHeader.Length() % 64);
    wadHeader.Append(headerPadding);
  }

  if (b_tmd.Length() % 64 != 0)
  {
    Buffer tmdPadding(pad, 64 - b_tmd.Length() % 64);
    b_tmd.Append(tmdPadding);
  }

  if (b_cert.Length() % 64 != 0)
  {
    Buffer certPadding(pad, 64 - b_cert.Length() % 64);
    b_cert.Append(certPadding);
  }

  //truncate to be sure that the ticket has the good length (due to nus)
  b_tik.Truncate(0x02A4ULL);
  if (b_tik.Length() % 64 != 0)
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

    tmdData = (tmd *) SIGNATURE_PAYLOAD((signed_blob*) b_tmd.Content());
    for (u32 cnt = 0; cnt < tmdData->num_contents; cnt++)
    {
      tmd_content *tmdContent = &tmdData->contents[cnt];
      Buffer b_content = GetContent(tmdContent->cid);

      if (b_content.Length() % 64 != 0)
      {
        Buffer contentPadding(pad, 64 - b_content.Length() % 64);
        b_content.Append(contentPadding);
      }
      wad.Write(b_content);
    }

    wad.Close();
    delete &wad;
  }
  catch (Exception& ex)
  {
    wad.Close();
    delete &wad;
    throw;
  }
  catch (...)
  {
    wad.Close();
    delete &wad;
    throw;
  }
}

void Title::Clean()
{
  // if already cleaned, we skip this
  if (_directory == "" || !Directory::Exists(_directory))
    return;

  Directory::Delete(_directory, true);
  string titleDir = Path::GetParentDirectory(_directory);
  if (Directory::IsEmpty(titleDir))
  {
    Directory::Delete(titleDir);
    string tempDirectory = Path::GetParentDirectory(titleDir);
    if (canDeleteRootTempDirectory && Directory::IsEmpty(tempDirectory))
      Directory::Delete(tempDirectory);
  }
}

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
    if (!processControl.skipStep)
    {
      u32 ticketLen = SIGNED_TIK_SIZE(
                        (signed_blob*) processControl.buffer.Content());
      ret = ES_AddTicket((signed_blob*) processControl.buffer.Content(),
                         ticketLen, (signed_blob*) certificate.Content(),
                         certificate.Length(), (signed_blob*) crl.Content(),
                         crl.Length());
      if (ret < 0)
        throw SystemException("Error installing ticket.", ret);

      INIT_PROCESS_CONTROL(processControl, NULL);
      OnTicketInstalled(processControl);
    }

    //Install tmd
    processControl.buffer = Tmd();
    INIT_PROCESS_CONTROL(processControl, NULL);
    OnTmdInstalling(processControl);
    if (!processControl.skipStep)
    {
      u32 tmdLen = SIGNED_TMD_SIZE(
                     (signed_blob*) processControl.buffer.Content());
      ret = ES_AddTitleStart(
              (signed_blob*) processControl.buffer.Content(), tmdLen,
              (signed_blob*) certificate.Content(), certificate.Length(),
              (signed_blob*) crl.Content(), crl.Length());
      if (ret < 0)
        throw SystemException("Error starting title installation.", ret);

      INIT_PROCESS_CONTROL(processControl, NULL);
      OnTmdInstalled(processControl);
    }

    Buffer tmdBuffer = processControl.buffer;
    tmd* tmdData = (tmd *) SIGNATURE_PAYLOAD(
                     (signed_blob*) tmdBuffer.Content());

    //Install contents
    for (u32 cnt = 0; cnt < tmdData->num_contents; cnt++)
    {
      tmd_content *tmdContent = &tmdData->contents[cnt];
      u32 cfd = 0;
      processControl.buffer = GetContent(tmdContent->cid);
      //Start content installation
      INIT_PROCESS_CONTROL(processControl, tmdContent);
      OnContentInstalling(processControl);
      if (!processControl.skipStep)
      {
        cfd = ES_AddContentStart(tmdData->title_id, tmdContent->cid);
        if (cfd < 0)
          throw SystemException("Error adding content start.", ret);

        //writing content datas
        ret = ES_AddContentData(cfd,
                                (u8*) processControl.buffer.Content(),
                                processControl.buffer.Length());
        if (ret < 0)
        {
          //if an error occures, we ensure to close the content
          //and notify the system of the error
          ES_AddContentFinish(cfd);
          throw SystemException("Error writing content.", ret);
        }

        //end content installation
        ret = ES_AddContentFinish(cfd);
        if (ret < 0)
          throw SystemException("Error finising content installation.", ret);

        INIT_PROCESS_CONTROL(processControl, tmdContent);
        OnContentInstalled(processControl);
      }
    }

    ret = ES_AddTitleFinish();
    if (ret < 0)
      throw SystemException("Error finising title installation", ret);
  }
  catch (AbortException &abort)
  {}
  catch (Exception &ex)
  {
    //Cancel install
    ES_AddTitleCancel();

    throw;
  }
  catch (...)
  {
    //Cancel install
    ES_AddTitleCancel();

    throw;
  }
}

void Title::Uninstall()
{
  Buffer tmdBuffer = Tmd();

  tmd* tmdData =
    (tmd *) SIGNATURE_PAYLOAD((signed_blob*) tmdBuffer.Content());
  Title::Uninstall(tmdData->title_id);
}

void Title::Uninstall(u64 titleId)
{
  tikview *viewData = NULL;
  u32 viewCnt;
  s32 ret;

  if (!Title::IsInstalled(titleId))
    return;

  if ((titleId & 0x100000000ULL) > 0ULL)
  {
    Title::UninstallUsingISFS(titleId);
    return;
  }

  ret = ES_GetNumTicketViews(titleId, &viewCnt);
  if (ret < 0)
    throw SystemException("Error getting view count.", ret);

  viewData = (tikview *) memalign(32, sizeof(tikview) * viewCnt);
  if (!viewData)
    throw Exception("Not enough memory.");

  try
  {
    ret = ES_GetTicketViews(titleId, viewData, viewCnt);
    if (ret < 0)
      throw SystemException("Error getting ticket views.", ret);

    /* Delete all tickets */
    for (u32 tickViewIndex = 0; tickViewIndex < viewCnt; tickViewIndex++)
    {
      ret = ES_DeleteTicket(&viewData[tickViewIndex]);
      if (ret < 0)
        throw SystemException("Error deleting title tickets.", ret);
    }

    // Delete title content
    ret = ES_DeleteTitleContent(titleId);
    if (ret < 0)
      throw SystemException("Error deleting title contents.", ret);

    //delete title
    ret = ES_DeleteTitle(titleId);
    if (ret < 0)
      throw SystemException("Error deleting title.", ret);
  }
  catch (...)
  {
    free(viewData);
    throw;
  }

  free(viewData);
}

void Title::UninstallUsingISFS(u64 titleId)
{
  u32 titleType = titleId >> 32;
  u32 id = (u32) titleId;

  stringstream ticketPath;
  ticketPath << "wii:/ticket/" << setw(8) << setfill('0') << hex << titleType
  << setw(0) << "/" << setw(8) << id << setw(0) << ".tik";

  stringstream titlePath;
  titlePath << "wii:/title/" << setw(8) << setfill('0') << hex << titleType
  << setw(0) << "/" << setw(8) << id;

  File::Delete(ticketPath.str());
  Directory::Delete(titlePath.str(), true);
}

vector<u8> Title::GetInstalledIos()
{
  vector < u8 > ioses;
  u32 nbTitle;
  u64 *titlesBuffer = NULL;
  s32 ret;
  //Get stored IOS versions.
  ret = ES_GetNumTitles(&nbTitle);
  if (ret < 0)
    throw SystemException("Error getting the number of installed titles.", ret);

  titlesBuffer = (u64*) memalign(32, sizeof(u64) * nbTitle);
  if (!titlesBuffer)
    throw Exception("Not enough memory.");

  try
  {
    ret = ES_GetTitles(titlesBuffer, nbTitle);
    if (ret < 0)
      throw SystemException("Error getting title list from nand.", ret);

    //filtering ios from other titles
    for (u32 titleIndex = 0; titleIndex < nbTitle; titleIndex++)
    {
      u32 type = *(u32*) (titlesBuffer + titleIndex);
      u32 number = (u32) titlesBuffer[titleIndex];

      //If IOS
      if (type == 1 && 2 < number && number < 0x100)
        ioses.push_back((u8) number);
    }
    free(titlesBuffer);
    titlesBuffer = NULL;
  }
  catch (...)
  {
    if (titlesBuffer)
      free(titlesBuffer);
    throw;
  }
  return ioses;
}

bool Title::IsInstalled(u64 titleId)
{
  u32 nbTitle;
  u64 *titlesBuffer = NULL;
  s32 ret;
  bool installed = false;

  //Get stored IOS versions.
  ret = ES_GetNumTitles(&nbTitle);
  if (ret < 0)
    throw SystemException("Error getting the number of installed titles.", ret);

  titlesBuffer = (u64*) memalign(32, sizeof(u64) * nbTitle);
  if (!titlesBuffer)
    throw Exception("Not enough memory.");

  try
  {
    ret = ES_GetTitles(titlesBuffer, nbTitle);
    if (ret < 0)
      throw SystemException("Error getting title list from nand.", ret);

    //filtering ios from other titles
    for (u32 titleIndex = 0; titleIndex < nbTitle; titleIndex++)
      if (*(titlesBuffer + titleIndex) == titleId)
      {
        installed = true;
        break;
      }

    free(titlesBuffer);
    titlesBuffer = NULL;
  }
  catch (...)
  {
    if (titlesBuffer)
      free(titlesBuffer);
    throw;
  }

  return installed;
}

u16 Title::GetInstalledTitleVersion(u64 titleId)
{
  u32 tmdLength;
  s32 ret;
  signed_blob* tmdBuffer = NULL;
  u16 titleVersion;

  /* Get TMD size */
  ret = ES_GetStoredTMDSize(titleId, &tmdLength);
  if (ret < 0)
    throw SystemException("Error getting TMD length", ret);

  /* Allocate memory */
  tmdBuffer = (signed_blob*) memalign(32, TITLE_ROUND_UP(tmdLength, 32));
  if (!tmdBuffer)
    throw Exception("Not enough memory.");

  /* Read TMD */
  ret = ES_GetStoredTMD(titleId, tmdBuffer, tmdLength);
  if (ret < 0)
  {
    free(tmdBuffer);
    throw SystemException("Error getting stored tmd.", ret);
  }

  titleVersion = ((tmd *) SIGNATURE_PAYLOAD(tmdBuffer))->title_version;
  free(tmdBuffer);

  return titleVersion;
}

void Title::CreateTempDirectory(u64 titleId, u16 revision,
                                const std::string& tempDirectory)
{
  if (Path::GetRoot(tempDirectory) == tempDirectory || Directory::Exists(
        tempDirectory))
    canDeleteRootTempDirectory = false;
  else
    canDeleteRootTempDirectory = true;

  stringstream str;
  str << tempDirectory << "/" << hex << setw(8) << setfill('0')
  << TITLE_TYPE(titleId);
  str << setw(0) << "/" << setw(8) << TITLE_ID(titleId) << setw(0)
  << setfill(' ') << dec;
  if (revision > 0)
    str << "v" << revision;

  _directory = str.str();
  _directory = Path::CleanPath(_directory);

  Directory::Create(_directory);
}

void Title::OnTicketInstalling(TitleEventArgs &processControl)
{
  TicketInstallingEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTicketInstalled(TitleEventArgs &processControl)
{
  TicketInstalledEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTmdInstalling(TitleEventArgs &processControl)
{
  TmdInstallingEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTmdInstalled(TitleEventArgs &processControl)
{
  TmdInstalledEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnContentInstalling(TitleEventArgs &processControl)
{
  ContentInstallingEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnContentInstalled(TitleEventArgs &processControl)
{
  ContentInstalledEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTicketLoading(TitleEventArgs &processControl)
{
  TicketLoadingEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTicketLoaded(TitleEventArgs &processControl)
{
  TicketLoadedEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTmdLoading(TitleEventArgs &processControl)
{
  TmdLoadingEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnTmdLoaded(TitleEventArgs &processControl)
{
  TmdLoadedEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnContentLoading(TitleEventArgs &processControl)
{
  ContentLoadingEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

void Title::OnContentLoaded(TitleEventArgs &processControl)
{
  ContentLoadedEvent(this, &processControl);
  if (processControl.abortProcess)
    throw AbortException();
}

bool Title::IsInstalled()
{
  Buffer tmdBuffer = Tmd();

  tmd* tmdData =
    (tmd *) SIGNATURE_PAYLOAD((signed_blob*) tmdBuffer.Content());
  return Title::IsInstalled(tmdData->title_id);
}

Title::~Title()
{
  if (automaticClean)
    Clean();
}

string Title::TempDirectory()
{
  return _directory;
}

string Title::GetWadFormatedName(u64 tid, u16 rev)
{
  stringstream wadName;
  u32 type = tid >> 32;
  u32 id = (u32) tid;
  if (type == 1) // If IOS
  {
    wadName << "IOS" << id;
    if (rev > 0)
      wadName << "-64-";
  } else
  {
    wadName << hex << setfill('0') << setw(8) << type << setw(0) << "-"
    << setw(8) << id << setw(0) << dec;
  }

  if (rev > 0)
    wadName << "v" << rev;

  wadName << ".wad";

  return wadName.str();

}

void Title::EncryptContent(Buffer& b, tmd_content* tmdInfo)
{
  u64 bufferLength = TITLE_ROUND_UP(b.Length(), 64);
  u8* outbuf = (u8*) memalign(32, bufferLength);
  if (!outbuf)
    throw Exception("Not enough memory.");

  /* Set IV key */
  u8 ivkey[16];
  memset(ivkey, 0, sizeof(ivkey));
  memcpy(ivkey, &tmdInfo->index, sizeof(tmdInfo->index));

  /* Set AES key */
  AES_SetKey(_titleKey);

  /* Decrypt content */
  AES_Encrypt(ivkey, (u8*) b.Content(), outbuf, bufferLength);

  /* Put the new hash */
  SHA1((u8*) b.Content(), tmdInfo->size, tmdInfo->hash);

  b.Clear();
  b.Append(outbuf, bufferLength);

  free(outbuf);
}

void Title::DecryptContent(Buffer& b, tmd_content* tmdInfo)
{
  u64 bufferLength = b.Length();
  u8* outbuf = (u8*) memalign(32, bufferLength);
  if (!outbuf)
    throw Exception("Not enough memory.");

  /* Set IV key */
  u8 ivkey[16];
  memset(ivkey, 0, sizeof(ivkey));
  memcpy(ivkey, &tmdInfo->index, sizeof(tmdInfo->index));

  /* Set AES key */
  AES_SetKey(_titleKey);

  /* Decrypt content */
  AES_Decrypt(ivkey, (u8*) b.Content(), outbuf, bufferLength);

  /* Check content hash */
  u8 hash[20];
  SHA1(outbuf, tmdInfo->size, hash);
  if (memcmp(hash, tmdInfo->hash, sizeof(hash)) != 0)
  {
    free(outbuf);
    stringstream str;
    str << "Content " << hex << tmdInfo->cid << dec
    << " decryption failed -> hash mismatch";
    throw Exception(str.str());
  }
  b.Clear();
  b.Append(outbuf, bufferLength);
  free(outbuf);
}

void Title::DecryptTitleKey(Buffer& b_tik)
{
  u8 commonkey[16] = { 0xeb, 0xe4, 0x2a, 0x22, 0x5e, 0x85, 0x93, 0xe4, 0x48,
                       0xd9, 0xc5, 0x45, 0x73, 0x81, 0xaa, 0xf7 };
  tik* p_tik = (tik*) SIGNATURE_PAYLOAD((signed_blob*) b_tik.Content());
  /* Set IV */
  u8 iv[16] ATTRIBUTE_ALIGN(32);
  memset(iv, 0, sizeof(iv));
  memcpy(iv, &p_tik->titleid, sizeof(u64));

  /* Set encrypted key */
  u8 enc[16] ATTRIBUTE_ALIGN(32);
  memset(enc, 0, sizeof(enc));
  memcpy(enc, &p_tik->cipher_title_key, sizeof(enc));

  /* Clear output buffer */
  u8 dec[16] ATTRIBUTE_ALIGN(32);
  memset(dec, 0, sizeof(dec));

  /* Decrypt title key */
  AES_SetKey(commonkey);
  AES_Decrypt(iv, enc, dec, sizeof(enc));
  memcpy(_titleKey, dec, sizeof(dec)); /* Copy title key */
}

Buffer Title::GetSharedContent(tmd_content* c)
{
  Buffer sharedMap = File::ReadToEnd("wii:/shared1/content.map");
  Buffer bsha(c->hash, 20);

  u64 index = sharedMap.Find(bsha);
  if (index == sharedMap.Length())
    throw SystemException("Shared content not found in content.map", c->index);

  stringstream str;
  char name[9];

  u8 * buf = (u8*) sharedMap.Content();
  sprintf(name, "%.8s", ((u8*) buf + index) - 8);
  str << "wii:/shared1/" << name << ".app";

  return File::ReadToEnd(str.str());
}

void Title::SaveDecryptedContent(const string& dirPath)
{
  if (!Directory::Exists(dirPath))
    Directory::Create(dirPath);

  Buffer b_tmd = Tmd();
  Buffer b_cetk = Ticket();
  b_cetk.Truncate(0x2a4);
  string actualDir = _directory;
  _directory = dirPath;
  Tmd(b_tmd);
  Ticket(b_cetk);
  _directory = actualDir;

  tmd* tmdData = (tmd *) SIGNATURE_PAYLOAD((signed_blob*) b_tmd.Content());

  for (u32 cnt = 0; cnt < tmdData->num_contents; cnt++)
  {
    tmd_content *tmdContent = &tmdData->contents[cnt];
    Buffer b_cnt = GetContent(tmdContent->cid);

    _directory = dirPath;

    DecryptContent(b_cnt, tmdContent);
    AddContent(b_cnt, tmdContent->cid);

    _directory = actualDir;
  }

}

void Title::ReloadIOS(u32 ios)
{
  s32 ret = 0;
  if (GetRunningIOS() != ios)
  {
    NetworkUtility::Deinit();
    Log::Pause();
    Device::EnsureShutdown();
    usleep(500000);
    ret = IOS_ReloadIOS(ios);
    usleep(500000);
    if (ret < 0)
      throw SystemException("Can't reload ios" + ios, ret);
    _runningIos = ios;
  }
}

u32 Title::GetRunningIOS()
{
  if (_runningIos == 0)
    _runningIos = IOS_GetVersion();

  return _runningIos;
}

std::string Title::GetType()
{
  return "Libwiisys::System::Title,"+Object::GetType();
}
