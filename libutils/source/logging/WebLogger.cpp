/*
 * WebLogger.cpp
 *
 *  Created on: 10 juin 2010
 *      Author: Clement
 */

#include <logging/WebLogger.h>
#include <com/NetworkUtility.h>
#include <com/HttpRequest.h>
#include <string>
#include <vector>
using namespace std;
WebLogger::WebLogger(std::string url) {
_url=url;
}

WebLogger::~WebLogger() {


}

void WebLogger::WriteError( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "type=error,message="<<message<<",line="<<line<<",file"<<file<<",appName="<<appName<<",appVersion="<<appVersion;
	Write(formatedMessage.str());
}

void WebLogger::WriteWarning( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
	stringstream formatedMessage;
	formatedMessage << "type=warning,message="<<message<<",line="<<line<<",file"<<file<<",appName="<<appName<<",appVersion="<<appVersion;
	Write(formatedMessage.str());
}

void WebLogger::WriteInfo( const std::string& message,int line,const char* file, const string& appName, const string& appVersion)
{
    stringstream formatedMessage;
	formatedMessage << "type=info,message="<<message<<",line="<<line<<",file"<<file<<",appName="<<appName<<",appVersion="<<appVersion;
	Write(formatedMessage.str());
}
/**
 *\brief Write a text to web output
 *\param text The text to write
 */
void WebLogger::Write( const std::string& text )
{
	HttpRequest r(_url);
	std::vector<std::string> v;
	v=UtilString::Split(text,',');
	for(u32 i=0;i<v.size();i++)
	{
		std::vector<std::string> v1=UtilString::Split(v[i],'=');
		r.AddParameter(v1[0],v1[1]);
	}
	r.GetResponse();

}

