#include <fs/File.h>
#include <com/Buffer.h>

File* f;

void init_debug_out()
{
	if(!File::Exists("sd:/debug.txt"))
		f = &(File::Create("sd:/debug.txt"));
	else
		f = &(File::Open("sd:/debug.txt", FileMode_Write));
}

void dbprintf(const std::string &message)
{
	static bool initiated = false;
	
	if(!initiated)
	{
		initiated = true;
		init_debug_out();
	}
	
	Buffer b(message.c_str(), message.size());
	f->Write(b);
	f->Close();
	delete f;
}