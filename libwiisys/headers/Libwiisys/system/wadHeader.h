#ifndef WADHEADER_H_
#define WADHEADER_H_

namespace Libwiisys
{
  namespace System
  {
    /**
     * \struct wad_header
     * \brief Represents a wadheader
     */
    typedef struct
    {
      /** Header length */
      u32 header_len;

      /** WAD type */
      char type[2];

      /** Padding data */
      u16 padding;

      /** Certificate length */
      u32 certs_len;

      /** crl length */
      u32 crl_len;

      /** ticket length */
      u32 tik_len;

      /** tmd length */
      u32 tmd_len;

      /** data(content) length */
      u32 data_len;

      /** footer length */
      u32 footer_len;
    }
    __attribute__((packed)) wad_header;

  }
}

#endif /* WADHEADER_H_ */
