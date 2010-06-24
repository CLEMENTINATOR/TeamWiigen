#ifndef _UI_MESSAGE_
#define _UI_MESSAGE_

#include <libwiisys.h>

#include <string>
#include <queue>

namespace UI
{
	class Message : public Libwiisys::Object
	{
	public:
		Message(std::string componentId, std::string tag, std::string parameters);

		std::string GetComponentId();
		std::string GetTag();
		std::string GetSerializedParameters();
		void AddStringParameter(std::string parameter);
		std::string GetStringParameter();
	private:
		std::string _componentId;
		std::string _tag;
		std::string _serializedParameters;
		std::queue<std::string> _stringParameters;
	};
}
#endif
