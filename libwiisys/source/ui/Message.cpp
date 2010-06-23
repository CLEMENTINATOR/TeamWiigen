#include <ui/Message.hpp>

using namespace UI;
using namespace std;

Message::Message(string componentId, string tag, string parameters)
: _componentId(componentId),
  _tag(tag),
  _serializedParameters(parameters)
{}

string Message::GetComponentId()
{
	return _componentId; 
}

string Message::GetTag()
{
	return _tag;
}

string Message::GetSerializedParameters()
{
	return _serializedParameters;
}

void Message::AddStringParameter(string parameter)
{
	_stringParameters.push(parameter); 
}

string Message::GetStringParameter()
{ 
	string param = _stringParameters.front();
	_stringParameters.pop(); 
	return param;
}
