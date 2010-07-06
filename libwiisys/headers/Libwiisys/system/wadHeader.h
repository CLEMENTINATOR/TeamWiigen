#ifndef WADHEADER_H_
#define WADHEADER_H_

namespace Libwiisys { namespace System {
/**
 * \struct wad_header
 * \brief Represents a wadheader
 */
typedef struct {
	/** Header length */
	u32 header_len;

	/** WAD type */
	char type[2];

	/** Padding data */
	u16 padding;

	/** Data length */
	u32 certs_len, crl_len, tik_len, tmd_len, data_len, footer_len;
} __attribute__((packed)) wad_header;

}}

#endif /* WADHEADER_H_ */
