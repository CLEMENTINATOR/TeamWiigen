#include <logging/ILogProvider.h>

ILogProvider::~ILogProvider()
{}

void ILogProvider::Start()
{
	if (paused) paused=false;
}

void ILogProvider::Pause()
{
	if(!paused) paused=true;
}
