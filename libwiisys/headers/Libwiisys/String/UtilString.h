#ifndef _UTILS_STRING_H_
#define _UTILS_STRING_H_

#include <string>
#include <vector>

#include <gctypes.h>
#include "../Object.h"

/*! \namespace Libwiisys::String
 * \brief Formating tools
 */
namespace Libwiisys {namespace String {

		/*!
		 * \class UtilString
		 * \brief Used to parse different types
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */
		class UtilString : public Object
		{
		public:
            virtual std::string GetType();
			/*!
			 * \brief Convert a const char* to is u64 representation.
			 * \param val The const char* to convert.
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \throw Exception if the input parameter is null
			 * \return the converted value
			 */
			static u64 ToU64(const char* val, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u64 representation.
			 * \param val The const char* to convert.
			 * \param defaultval Value used if val parameter is NULL
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \return The parsed value of defaultVal if the input is NULL
			 */
			static u64 ToU64(const char* val, u64 defaultval, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u32 representation.
			 * \param val The const char* to convert.
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \throw Exception if the input parameter is null
			 * \return The converted value
			 */
			static u32 ToU32(const char* val, NumberRepresentation rep = nr_normal);

			/**
			 * \brief Convert a const char* to is u32 representation.
			 * \param val The const char* to convert.
			 * \param defaultval Value used if val parameter is NULL
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \return the converted value or defaultval if val==NULL
			 */
			static u32 ToU32(const char* val, u32 defaultval, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u32 representation.
			 * \param val The const char* to convert.
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \throw Exception if the input parameter is null
			 * \return The converted value
			 */
			static u16 ToU16(const char* val, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u16 representation.
			 * \param val The const char* to convert.
			 * \param defaultval The default value if val is NULL
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \return The converted value or default val
			 */
			static u16 ToU16(const char* val, u16 defaultval, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u8 representation.
			 * \param val The const char* to convert.
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \throw Exception if the input parameter is null
			 * \return The converted value
			 */
			static u8 ToU8(const char* val, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u8 representation.
			 * \param val The const char* to convert.
			 * \param defaultval The defaultvalue is value == NULL
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \return The converted value or default val
			 */
			static u8 ToU8(const char* val, u8 defaultval, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is s32 representation.
			 * \param val The const char* to convert.
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \throw Exception if the input parameter is null
			 * \return The converted value
			 */
			static s32 ToS32(const char* val, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u32 representation.
			 * \param val The const char* to convert.
			 * \param defaultval the default value if val==NULL
			 * \param rep Is used to know how to parse the string. The default value is nr_normal
			 * \return The converted value or default val
			 */
			static s32 ToS32(const char* val, s32 defaultval, NumberRepresentation rep = nr_normal);

			/*!
			 * \brief Convert a const char* to is u32 representation.
			 * \param val The const char* to convert.
			 * \throw Exception if the input parameter is null
			 * \return The converted value
			 */
			static bool ToBool(const char* val);

			/*!
			 * \brief Convert a const char* to is u32 representation.
			 * \param val The const char* to convert.
			 * \param defaultval the default val if val==NULL
			 * \return The converted value or default val
			 */
			static bool ToBool(const char* val, bool defaultval);

			/*!
			 * \brief Convert a const char* to is string representation.
			 * \param value The const char* to convert.
			 * \throw Exception if the input parameter is null
			 * \return the converted value
			 */
			static std::string ToStr(const char* value);

			/*!
			 * \brief Convert a const char* to is string representation.
			 * \param value The const char* to convert.
			 * \param defaultVal Value used if value parameter is NULL
			 * \return The parsed value or defaultVal if the input is NULL
			 */
			static std::string ToStr(const char* value, const std::string& defaultVal);

			/**
			 * \brief Convert a string to its wstring representation.
			 * \param str The string to convert.
			 * \return The converted value
			 */
			static std::wstring StrToWstr(const std::string& str);

			/**
			 * \brief Convert a wstring to its string representation.
			 * \param wstr The wstring to convert.
			 * \return The converted value
			 */
			static std::string WstrToStr(const std::wstring& wstr);

			/**
			 *\brief Remplace in a string a pattern with the given value
			 *\param source the source string
			 *\param pattern The pattern to be remplaced
			 *\param value The value which will remplace the pattern
			 *\return The remplaced string
			 */
			static std::string Replace(const std::string& source, const std::string& pattern, const std::string& value);

			/**
			 * \brief Split a string with the given splitcaracter in a vector or string
			 * \param str The string to split
			 * \param split The caracted used to split the string
			 * \param removeEmpty If true, remove automatically the empty splited parts (default = false)
			 * \return a vector with the splited strings
			 */
			static std::vector<std::string> Split(const std::string& str, const char split, bool removeEmpty = false);
		};

	}}

#endif
