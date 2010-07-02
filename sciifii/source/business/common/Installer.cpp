#include "Installer.h"

using namespace std;

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

s8 Installer::Region()
{
	return _region;
}

void Installer::Region(s8 r)
{
	_region = r;
}
