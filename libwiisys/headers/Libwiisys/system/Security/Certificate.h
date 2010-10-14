#ifndef _CERTIFICATE_H_
#define _CERTIFICATE_H_

#include "../../Object.h"
#include "../../Buffer.h"
#include <ogcsys.h>

#define CERTIFICATE_LEN 0x280
namespace Libwiisys
{
  namespace System
  {
    namespace Security
    {
      /**
       * \class Certificate
       * \brief This class handles the use of Wii Certificate.
       * \author Arasium, Teton, Fanta
       * \version 1.0
       */

      class Certificate : public Object
      {
        public:

          /*!
           * \brief Get the cert content
           * \return The certs buffer
           */
          static signed_blob* GetContent();

          /*!
           * \brief Get the certs length
           * \return The certs length
           */
          static u32 GetLength();

        private:
          Buffer content;

          /*!
           * \brief Get the cert reference
           * \return A certificate object
           * \see Certificate
           */
          static Certificate& Current();

          /*!
           * \brief Constructor
           * Loads the wii certs in memory
           */
          Certificate();
      };
    }
  }
}
#endif
