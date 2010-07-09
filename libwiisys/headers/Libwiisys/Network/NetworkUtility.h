#ifndef NETWORKUTILITY_H_
#define NETWORKUTILITY_H_

#include <string>

namespace Libwiisys {namespace Network {

		/**
		 * \author Teton, Arasium, Fanta
		 * \version 1.0
		 * \class NetworkUtility
		 * @brief A class to manage networking
		 */
		class NetworkUtility {
		public:

			/**
			 *\brief Constructor
			 */
			NetworkUtility();

			/**
			 *\brief Destructor
			 */
			virtual ~NetworkUtility();

			/*!
			 * \brief Gets the wii IP
			 * \return the ip on a string array
			 */
			static std::string GetIp(void);

			/**
			 *\brief Return the current NetworkUtility
			 *\return The current NetworkUtility
			 */
			static NetworkUtility &Current();

			/*!
			 * \brief UrlEncoding
			 * \param s The string to urlencode
			 * \return the urlencoded
			 */
			static std::string URLEncode(std::string s);

			/*!
			 * \brief Deinit networking
			 */
			static void Deinit();
		private :
			std::string _hostIp;

			/**
			 *\brief Return if the NetworkUtility has been initialized
			 *\return The current NetworkUtility
			 */
			static bool& Initialized();

		};

	}}

#endif /* NETWORKUTILITY_H_ */
