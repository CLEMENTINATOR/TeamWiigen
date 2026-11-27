#ifndef _RIJNDAEL_H_
#define _RIJNDAEL_H_

#include <gctypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Prototypes */
void AES_SetKey(u8 *);
void WS_AES_Decrypt(u8 *, u8 *, u8 *, u64);
void WS_AES_Encrypt(u8 *, u8 *, u8 *, u64);

#ifdef __cplusplus
}
#endif
#endif
