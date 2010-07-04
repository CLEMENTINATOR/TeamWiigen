#include <sstream>
#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

/*!
 * \brief Convert a const char* to is string representation.
 * \param value The string to convert.
 * \throw Exception if the input parameter is null
 * \return the converted value
 */
string UtilString::ToStr(const char* value)
{
	if (!value)
		throw Exception("Cannot parse NULL value to string", -1);

	return string(value);
}

/*!
 * \brief Convert a const char* to is string representation.
 * \param value The string to convert.
 * \param defaultVal Value used if value parameter is NULL
 * \return The parsed value or defaultVal if the input is NULL
 */
string UtilString::ToStr(const char* value, const string& defaultVal)
{
	if (!value)
		return defaultVal;

	return string(value);
}

/*!
 * \brief Convert a const char* to is u64 representation.
 * \param val The string to convert.
 * \param defaultval Value used if val parameter is NULL
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \return The parsed value of defaultVal if the input is NULL
 */
u64 UtilString::ToU64(const char* val, u64 defaultval, NumberRepresentation rep)
{
	if (val == NULL)
		return defaultval;

	stringstream str(val);
	u64 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u64 representation.
 * \param val The string to convert.
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \throw Exception if the input parameter is null
 * \return the converted value
 */
u64 UtilString::ToU64(const char* val, NumberRepresentation rep)
{
	if (val==NULL)
		throw Exception("Cannot parse NULL value to u64", -1);

	stringstream str(val);
	u64 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/**
 * \brief Convert a const char* to is u32 representation.
 * \param val The string to convert.
 * \param defaultval Value used if val parameter is NULL
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \return the converted value or defaultval if val==NULL
 */
u32 UtilString::ToU32(const char* val, u32 defaultval, NumberRepresentation rep)
{
	if (val==NULL) return defaultval;

	stringstream str(val);
	u32 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u32 representation.
 * \param val The string to convert.
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \throw Exception if the input parameter is null
 *\return The converted value
 */
u32 UtilString::ToU32(const char* val, NumberRepresentation rep)
{
	if (val==NULL)
		throw Exception("Cannot parse NULL value to u32", -1);
	stringstream str(val);
	u32 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u16 representation.
 * \param val The string to convert.
 * \param defaultval The default value if val is NULL
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \return The converted value or default val
 *
 */
u16 UtilString::ToU16(const char* val, u16 defaultval, NumberRepresentation rep)
{
	if (val==NULL) return defaultval;
	stringstream str(val);
	u16 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u32 representation.
 * \param val The string to convert.
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \throw Exception if the input parameter is null
 * \return The converted value

 */
u16 UtilString::ToU16(const char* val, NumberRepresentation rep)
{
	if (val==NULL)
		throw Exception("Cannot parse NULL value to u16", -1);
	stringstream str(val);
	u16 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u8 representation.
 * \param val The string to convert.
 * \param defaultval The defaultvalue is value == NULL
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \return The converted value or default val

 */
u8 UtilString::ToU8(const char* val, u8 defaultval, NumberRepresentation rep)
{
	if (val==NULL)
		return defaultval;

	stringstream str(val);
	u16 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;

	return (u8)returnValue;
}

/*!
 * \brief Convert a const char* to is u8 representation.
 * \param val The string to convert.
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \throw Exception if the input parameter is null
 * \return The converted value

 */
u8 UtilString::ToU8(const char* val, NumberRepresentation rep)
{
	if (val==NULL)
		throw Exception("Cannot parse NULL value to u8", -1);

	stringstream str(val);
	u16 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return (u8)returnValue;
}

/*!
 * \brief Convert a const char* to is s32 representation.
 * \param val The string to convert.
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \throw Exception if the input parameter is null
 * \return The converted value

 */
s32 UtilString::ToS32(const char* val, NumberRepresentation rep)
{
	if (val==NULL)
		throw Exception("Cannot parse NULL value to s32", -1);
	stringstream str(val);
	s32 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u32 representation.
 * \param val The string to convert.
 * \param defaultval the default value if val==NULL
 * \param rep Is used to know how to parse the string. The default value is nr_normal
 * \return The converted value or default val
 */
s32 UtilString::ToS32(const char* val,  s32 defaultval,NumberRepresentation rep)
{
	if (val==NULL) return defaultval;
	stringstream str(val);
	s32 returnValue;

	if (rep == nr_hex)
		str >> hex;

	str >> returnValue;
	return returnValue;
}

/*!
 * \brief Convert a const char* to is u32 representation.
 * \param val The string to convert.
 * \throw Exception if the input parameter is null
 * \return The converted value
 */
bool UtilString::ToBool(const char* val)
{
	if (val==NULL)
		throw Exception("Cannot parse NULL value to bool", -1);

	string value(val);

	if (value == "true")
		return true;
	else if (value == "false")
		return false;
	else
		throw Exception("Error parsing bool value", -1);
}

/*!
 * \brief Convert a const char* to is u32 representation.
 * \param val The string to convert.
 * \param defaultval the default val if val==NULL
 * \return The converted value or default val
 *
 */
bool UtilString::ToBool(const char* val,bool defaultval)
{
	if (val==NULL) return defaultval;
	string value=ToStr(val);
	if (value == "true")
		return true;
	else if (value == "false")
		return false;
	else
		throw Exception("Error parsing bool value", -1);
}
/**
 *\brief Split a string with the given splitcaracter in a vector or string
 *\param str The string to split
 *\param splitCaracter The caracted used to split the string
 * \return a vector with the splited strings
 */
vector<string> UtilString::Split(const string& str, const char splitCaracter, bool removeEmpty)
{
	vector<string> voptions;
	string modeOptions = str;
	u32 position = 0;

	while ((position = modeOptions.find_first_of(splitCaracter)) != string::npos)
	{
		string item = modeOptions.substr(0, position);
		if(!removeEmpty || item != "")
			voptions.push_back(item);
		modeOptions = modeOptions.erase(0, position + 1);
	}

	if(!removeEmpty || modeOptions != "")
		voptions.push_back(modeOptions);

	return voptions;
}
/**
 *\brief Remplace in a string a pattern with the given value
 *\param source the source string
 *\param pattern The pattern to be remplaced
 *\param value The value which will remplace the pattern
 *\return The remplaced string
 */
string UtilString::Replace(const string& source, const string& pattern, const string& value)
{
	string temp = source;
	size_t found;

	while((found = temp.find(pattern)) != string::npos)
	{
		temp = temp.replace(found, pattern.length(), value);
	}

	return temp;
}

wstring UtilString::StrToWstr(const string& str)
{
	wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;
}

string UtilString::WstrToStr(const wstring& wstr)
{
	string str;
	str.assign(wstr.begin(), wstr.end());
	return str;
}
