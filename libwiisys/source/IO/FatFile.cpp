#include <malloc.h>
#include <sys/stat.h>
#include <Libwiisys/IO/FatFile.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;


FatFile::FatFile(FILE *fd, const string &fileName)
{
  this->_fd = fd;
  _fileName = fileName;

  fseek(fd, 0, SEEK_END);
  _fileLength = ftell(fd);
  fseek(fd, 0, SEEK_SET);
}


bool FatFile::Exists(const string &fileName)
{
  struct stat st;
  if (stat(fileName.c_str(), &st) < 0)
    return false;

  if (!S_ISDIR(st.st_mode))
    return true;
  else
    return false;
}


FatFile& FatFile::Open(const string &fileName, const string &mode)
{
  if (!FatFile::Exists(fileName))
    throw Exception("The file to open doesn't exists!");

  FILE *fd = fopen(fileName.c_str(), mode.c_str());
  if (!fd)
    throw Exception("Error opening file : " + fileName);

  return *(new FatFile(fd, fileName));
}


void FatFile::Close()
{
  if (fclose(_fd) == EOF)
    throw Exception("Error closing file!");

  _fd = NULL;

  File::Close();
}


void FatFile::Delete(const string &fileName)
{
  if (!FatFile::Exists(fileName))
    return;

  if (remove(fileName.c_str()))
    throw Exception("Error deleting " + fileName);
}


FatFile& FatFile::Create(const string &fileName)
{
  if (FatFile::Exists(fileName))
    throw Exception("Can't create " + fileName + " already exists!");

  FILE *fd = fopen(fileName.c_str(), "wb");
  if (!fd)
    throw Exception("Error creating file : " + fileName);

  return *(new FatFile(fd, fileName));
}


void FatFile::Write(const Buffer& b)
{
  u32 pageSize = 1024;
  u32 totalToRight = b.Length();
  u32 nbWritten = 0;
  u32 nbToRight = 0;
  u32 nbWrited = 0;

  while (totalToRight > 0)
  {
    if (totalToRight < pageSize)
      nbToRight = totalToRight;
    else
      nbToRight = pageSize;

    nbWrited = fwrite((u8*) b.Content() + nbWritten, 1, nbToRight, _fd);
    if (nbWrited == 0)
      throw Exception((char*) "Error writing file!");

    nbWritten += nbWrited;
    totalToRight -= nbWrited;
  }
}


u32 FatFile::Read(Buffer& b, u32 len, u32 offset)
{
  if(offset != (u32)-1)
  {
    if(offset + len > _fileLength)
      throw SystemException("Can't read the file. "+_fileName+" will be reached.", (offset+len)-_fileLength);

    Seek(offset);
  }

  void* tempBuffer = malloc(len);
  if(tempBuffer == NULL)
  {
	   throw SystemException((char*) "Out of memory FatFile::Read");
  }
  s32 nbLus = fread(tempBuffer, 1, len, _fd);

  if (nbLus < 0)
  {
    free(tempBuffer);
    throw SystemException((char*) "Error reading file!", nbLus);
  }

  b.Append(tempBuffer, nbLus);
  free(tempBuffer);
  return (u32) nbLus;
}

void FatFile::Seek(u32 offset)
{
  if(offset > _fileLength)
    throw SystemException("Can't seek out of the file.", offset-_fileLength);

  fseek(_fd, offset, SEEK_SET);
}

FatFile::~FatFile()
{
  if (_fd)
    Close();
}

std::string FatFile::GetType()
{
  return "Libwiisys::IO::FatFile,"+File::GetType();
}
