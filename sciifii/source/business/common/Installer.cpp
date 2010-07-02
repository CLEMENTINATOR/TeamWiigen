#include "Installer.h"
#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::String;

void Installer::OnProgress(const std::string& message, f32 value)
{
	ProgressEventArgs arg;
	arg.message = message;
	arg.percent = value;
	Progressing(this, &arg);
}

void Installer::OnWarning(const std::string& message, f32 value)
{
	ProgressEventArgs arg;
	arg.message = message;
	arg.percent = value;
	Warning(this, &arg);
}
void Installer::SendToLog()
{
}
Installer::~Installer()
{}

string Installer::Options()
{
	return _options;
}

void Installer::Options(const string &o)
{
	_options = o;
}

vector<s8>& Installer::Region()
{
	return _regions;
}

void Installer::Region(string r)
{
	_regions.clear();
  vector<string> regions = UtilString::Split(r, ',');
  
  for(vector<string>::iterator ite = regions.begin(); ite != regions.end(); ite++)
  {
    stringstream str(*ite);
    s32 region;
    str >> region;
    _regions.push_back(region);
  }
}

vector<s32>& Installer::IgnoredExceptions()
{
  return _ignoredExceptions;
}

void Installer::IgnoredExceptions(const string& exceptionsList)
{
  _ignoredExceptions.clear();
  vector<string> exceptions = UtilString::Split(exceptionsList, ',');
  
  for(vector<string>::iterator ite = exceptions.begin(); ite != exceptions.end(); ite++)
  {
    stringstream str(*ite);
    s32 exceptionCode;
    str >> exceptionCode;
    _ignoredExceptions.push_back(exceptionCode);
  }
}