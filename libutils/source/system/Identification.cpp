#include <gccore.h>

#include <certs_dat.h>
#include <fake_su_tmd_dat.h>
#include <fake_su_ticket_dat.h>

#include <system/Identification.h>
#include <exception/Exception.h>

/*!
 * \brief Identify module
 * \param user The UserType mode you need
 */
void Identification::IdentifyAs(UserType user)
{
	if(user == UserType_SU)
	{
		Identify(certs_dat, certs_dat_size, fake_su_tmd_dat, fake_su_tmd_dat_size, fake_su_ticket_dat, fake_su_ticket_dat_size);
	}
	else if(user == UserType_SystemMenu)
	{
		throw Exception("Not implemented.",-1);
	}
	else
		throw Exception("Unknown user. Can't identify as this user.", user);
}

/*!
 * \brief Identify fonction
 * \see IdentifyAs()
 */
void Identification::Identify(const u8 *certs, u32 certs_size, const u8 *idtmd, u32 idtmd_size, const u8 *idticket, u32 idticket_size)
{
	s32 ret;
	u32 keyid = 0;
	ret = ES_Identify((signed_blob*)certs, certs_size, (signed_blob*)idtmd, idtmd_size, (signed_blob*)idticket, idticket_size, &keyid);
	if (ret < 0)
	{
		switch(ret)
		{
			case ES_EINVAL:
				throw Exception("Error! ES_Identify Data invalid!", ret);
			case ES_EALIGN:
				throw Exception("Error! ES_Identify Data not aligned!", ret);
			case ES_ENOTINIT:
				throw Exception("Error! ES_Identify ES not initialized!", ret);
			case ES_ENOMEM:
				throw Exception("Error! ES_Identify No memory!", ret);
			default:
				throw Exception("Error! ES_Identify", ret);
		}
	}
}
