
#ifndef PROGRESSEVENTARGS_HPP_
#define PROGRESSEVENTARGS_HPP_
namespace Libwiisys
{
namespace Threading
{
class ProgressEventArgs: public EventArgs
{
public :
	u32 progress;
	std::string msg;
};
}
}
#endif /* PROGRESSEVENTARGS_HPP_ */
