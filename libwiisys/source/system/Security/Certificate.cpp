#include <libwiisys.h>
#include <stdlib.h>

#include "../../../build/certs_dat.h"

using namespace Libwiisys::System::Security;

Certificate::Certificate() :
	content(certs_dat, certs_dat_size) {
}

Certificate& Certificate::Current() {
	static Certificate cert;

	return cert;
}

signed_blob* Certificate::GetContent() {
	return (signed_blob*) Current().content.Content();
}

u32 Certificate::GetLength() {
	return Current().content.Length();
}
