#include <libwiisys.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace Libwiisys::System::Patching;
using namespace Libwiisys::System::Event;

Patch::Patch(const std::string &module) :
	AllowedModule(module), ForbiddenModule() {
}

Patch::Patch(const Patch& patch) :
	AllowedModule(patch.AllowedModule), ForbiddenModule(patch.ForbiddenModule) {
}

Patch& Patch::operator=(const Patch& patch) {
	AllowedModule = patch.AllowedModule;
	ForbiddenModule = patch.ForbiddenModule;

	return *this;
}

Patch::~Patch() {
}

bool Patch::IsModule(const Buffer& b, const string& module) const {
	string str = "$IOSVersion:";
	char* buf = (char*) b.Content();

	for (u64 cnt = 0; cnt < (b.Length() - str.size()); cnt++)
		/* Module string found */
		if (strncmp(str.c_str(), buf + cnt, str.length()) == 0) {
			cnt += str.length();
			while (buf[cnt] == ' ')
				cnt++;
			if (strncmp(module.c_str(), buf + cnt, module.length()) == 0)
				return true;
		}

	return false;
}

bool Patch::CanPatch(const Buffer& b) const {
	if (AllowedModule.length() == 0)
		return true;

	if (!IsModule(b, AllowedModule))
		return false;

	if (ForbiddenModule.length() != 0 && IsModule(b, ForbiddenModule))
		return false;

	return true;
}


u32 Patch::ApplyPatch(TitleEventArgs &processControl) const {
	if (!CanPatch(processControl.buffer))
		return 0;

	return Patching(processControl);
}

std::string Patch::GetType()
{
	return "Libwiisys::System::Patching::Patch,"+Object::GetType();
}

