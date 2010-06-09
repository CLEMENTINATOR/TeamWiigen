#ifndef _ILOGPROVIDER_H_
#define _ILOGPROVIDER_H_

#include <string>
#include <gctypes.h>

class ILogProvider
{
public:
	virtual ~ILogProvider() = 0;
	virtual void WriteError( const std::string& message, s32 errorCode,int line,const char* file) = 0;
	virtual void WriteWarning( const std::string& message, s32 warningCode,int line,const char* file) = 0;
	virtual void WriteInfo( const std::string& message, s32 infoCode,int line,const char* file) = 0;
	virtual void Start();
	virtual void Pause();
protected :
	bool paused;
};

#endif
