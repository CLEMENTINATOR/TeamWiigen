#ifndef _UTILS_XML_H
#define _UTILS_XML_H

#include <string>
#include <tinyxml.h>

/*! \namespace Libwiisys::Serialization
 * \brief Serialization tool
 *
 * Only Xml tools actually.
 */
namespace Libwiisys {namespace Serialization {

		/**
		 *\class Xml
		 *\brief Loads XML Files (tinyxml needed !)
		 *\author Arasium,Teton,Fanta
		 *\version 1.0
		 */
		class Xml
		{
		public:

			/**
			 *\brief Load the xml specified by path
			 *\param file The file path
			 *\return The TiXmlDocument loaded
			 */
			static TiXmlDocument& Load(const std::string &file);
		};

	}}

#endif
