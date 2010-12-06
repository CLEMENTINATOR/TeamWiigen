#include <Libwui/Audio/MP3/EQState.h>

using namespace Libwui::Audio::MP3;

static f32 VSA = (1.0/4294967295.0);

EQState::EQState(s32 lowfreq, s32 highfreq, s32 mixfreq)
{
	f1p0 = 0;
	f1p1 = 0;
	f1p2 = 0;
	f1p3 = 0;

	f2p0 = 0;
	f2p1 = 0;
	f2p2 = 0;
	f2p3 = 0;

	sdm1 = 0;
	sdm2 = 0;
	sdm3 = 0;
	
	lg = 1.0;
	mg = 1.0;
	hg = 1.0;
	
	lf = 2.0F * sinf(M_PI * ((f32)lowfreq / (f32)mixfreq));
	hf = 2.0F * sinf(M_PI * ((f32)highfreq / (f32)mixfreq));
}

s16 EQState::Do(s16 sample)
{
	f32 l,m,h;

	f1p0 += (lf*((f32)sample - f1p0))+VSA;
	f1p1 += (lf*(f1p0 - f1p1));
	f1p2 += (lf*(f1p1 - f1p2));
	f1p3 += (lf*(f1p2 - f1p3));
	l = f1p3;

	f2p0 += (hf*((f32)sample - f2p0))+VSA;
	f2p1 += (hf*(f2p0 - f2p1));
	f2p2 += (hf*(f2p1 - f2p2));
	f2p3 += (hf*(f2p2 - f2p3));
	h = sdm3 - f2p3;

	m = sdm3 - (h+l);

	l *= lg;
	m *= mg;
	h *= hg;

	sdm3 = sdm2;
	sdm2 = sdm1;
	sdm1 = (f32)sample;

	return (s16)(l+m+h);
}