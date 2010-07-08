#include <libwiisys.h>
#include <stdlib.h>

#include "../../build/certs_dat.h"

using namespace Libwiisys::System::Security;

/*!
 * \brief Constructor
 * Loads the wii certs in memory
 */
Certificate::Certificate()
: content(certs_dat, certs_dat_size)
{}

/*!
 * \brief Get the cert reference
 * \return A certificate object
 * \see Certificate
 */
Certificate& Certificate::Current()
{
	static Certificate cert;

	return cert;
}

/*!
 * \brief Get the cert content
 * \return The certs buffer
 */
signed_blob* Certificate::GetContent()
{
	return (signed_blob*)Current().content.Content();
}

/*!
 * \brief Get the certs length
 * \return The certs length
 */
u32 Certificate::GetLength()
{
	return Current().content.Length();
}
