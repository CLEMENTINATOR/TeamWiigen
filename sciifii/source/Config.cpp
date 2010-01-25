#include "Config.h"
#include <libutils/com/NetworkRequest.h>
/*
 * For cios corp 3.6
 */
 
ciosDesc installCioses[] = {
{	9,	60,	6174,	13,	0,	true,	false,	true,	""},
{	11,	60,	6174,	13, 0,	true,	false,	true,	""},
{	17,	53,	5149,	17, 0,	false,	false,	true,	""},
{	20,	60,	6174,	13, 0,	true,	false,	true,	""},
{	21,	53,	5149,	17, 0,	false,	false,	true,	""},
{	28,	28,	1293,	17, 0, 	false,	false,	false,	""},
{	30,	60,	6174,	13,	0, 	true,	false,	true,	""},
{	33,	33,	2834,	17, 0, 	false,	false,	false,	""},
{	35,	35,	3092,	17, 0, 	true,	false,	false,	""},
{	36,	36,	3094,	13,	0, 	true,	true,	false,	""},
{	37,	37,	3612,	17, 0,	true,	true,	true,	""},
{	38,	38,	3610,	17, 17, false,	false,	false,	""},
{	40,	60,	6174,	13,	0, 	true,	false,	true,	""},
{	41,	41,	3091,	17,	0, 	false,	false,	true,	""},
{	43,	43,	3091,	17,	0, 	false,	false,	true,	""},
{	45,	45,	3091,	17,	0, 	false,	false,	true,	""},
{	46,	46,	3093,	17,	0, 	false,	false,	true,	""},
{	50,	50,	4889,	13,	0, 	true,	false,	true,	""},
{	52,	52,	5661,	13,	0, 	true,	false,	true,	""},
{	53,	53,	5149,	17, 0, 	false,	false,	true,	""},
{	55,	55,	5149,	17, 0, 	false,	false,	true,	""},
{	56,	56,	5146,	17, 0, 	false,	false,	true,	"http://dmanspokehackland.webs.com/cIOSCORP/IOS56-64-v5146.wad"}, //need url
{	58,	58,	5918,	17,	0,	false,	false,	false, 	"http://dmanspokehackland.webs.com/cIOSCORP/IOS58-64-v5918.wad"},
{	60,	60,	6174,	13,	0, 	true,	false,	true,	""},
{	70,	60,	6174,	13,	0, 	true,	false,	true,	""},
};

bool allowIllegal = true;

const u64 NB_INSTALL_CIOS = 25;

bool hasNetwork = true;

u16 ios15Revision = 257;

void ConfigureSciifii()
{
	try { NetworkRequest::GetIp(); }
	catch(...) { hasNetwork = false; }
}
