#ifndef _TEST_NETWORK_REQUEST_
#define _TEST_NETWORK_REQUEST_

#include <map>
#include <ogcsys.h>
#include <string>
#include "../Object.h"
#include "../Buffer.h"
#include <sstream>

/*! \namespace Libwiisys::Network
 * \brief Http and Web utilities
 *
 * This contains tools to manipulate Http request and
 * tools to download items from NUS.
 */
namespace Libwiisys {namespace Network {

		/**
		 * \class HttpRequest
		 * \brief This class allow the use of HTTP (GET) request
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */
		class HttpRequest : public Object
		{
		public:

			/*!
			 * \brief Constructor
			 */
			HttpRequest();

			/*!
			 * \brief Overloaded constructor
			 * \param url the full url for the request
			 */
			HttpRequest(const std::string& url);


			/*!
			 * \brief Destructor
			 */
			~HttpRequest();

			/*!
			 * \brief Get the server response
			 * \return A buffer containing the reponse
			 */
			Buffer GetResponse();

			/*!
			 * \brief Get the server response and check sha1 hash
			 *\param sha The sha buffer
			 * \return A buffer containing the reponse
			 */
			Buffer GetResponse(const Buffer& sha);

			/*!
			 * \brief Get the server response and check sha1 hash
			 *\param shaUrl The sha1 url
			 * \return A buffer containing the reponse
			 */
			Buffer GetResponse(const std::string& shaUrl);

			/*!
			 * \brief Set an new http request
			 * \param url the server url (needs to begin by "http://www.)
			 */
			void SetRequest(const std::string& url);

			/**
			 * @brief Add a parameter to the request -> url?key1="value1"&key2="value2" etc
			 * @param key A parameter key
			 * @param value The value associated to the key
			 */
			void AddParameter(const std::string& key, const std::string& value);

		private:
			s32 sockfd;
			std::string _url;
			std::string _hostName;
			std::string _path;
			std::map<std::string, std::string> _params;

			/*!
			 * \brief Connect
			 * \param hostname The hostname of the server
			 */
			void Connect(std::string hostname);

			/*!
			 * \brief Read data from the serv
			 * \param b The Buffer where you want to store the readed data
			 * \param len The len of the readed content
			 * \return The length read
			 */
			s32 Read(Buffer& b, u32 len);

			/*!
			 * \brief Send data to the serv
			 * \param b The buffer to be writted
			 * \return The length writen
			 */
			s32 Write(Buffer &b);

			/*!
			 * \brief Get the length of the network response
			 * \return The length of the contents
			 */
			u32 GetResponseLength();
		};

	}}

#endif
