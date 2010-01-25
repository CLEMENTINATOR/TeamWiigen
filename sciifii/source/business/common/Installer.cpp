#include "Installer.h"

using namespace std;

Installer::Installer(const string& folder)
: wadFolder(folder)
{}

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
