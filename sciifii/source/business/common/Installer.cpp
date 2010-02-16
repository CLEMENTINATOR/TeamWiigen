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
