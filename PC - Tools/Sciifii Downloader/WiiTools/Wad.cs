using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace WiiTools
{
    class Wad
    {
        byte[] tmd;
        byte[] ticket;
        List<byte[]> contents;
        byte[] cert;
		
		static int TicketSize = 0x2A4;

        static byte[] cert_CA = new Byte[0x400];
        static byte[] cert_CACP = new Byte[0x300];
        static byte[] cert_CAXS = new Byte[0x300];

        static byte[] cert_CA_sha1 = new byte[20] { 0x5B, 0x7D, 0x3E, 0xE2, 0x87, 0x06, 0xAD, 0x8D, 0xA2, 0xCB, 0xD5, 0xA6, 0xB7, 0x5C, 0x15, 0xD0, 0xF9, 0xB6, 0xF3, 0x18 };
        static byte[] cert_CACP_sha1 = new byte[20] { 0x68, 0x24, 0xD6, 0xDA, 0x4C, 0x25, 0x18, 0x4F, 0x0D, 0x6D, 0xAF, 0x6E, 0xDB, 0x9C, 0x0F, 0xC5, 0x75, 0x22, 0xA4, 0x1C };
        static byte[] cert_CAXS_sha1 = new byte[20] { 0x09, 0x78, 0x70, 0x45, 0x03, 0x71, 0x21, 0x47, 0x78, 0x24, 0xBC, 0x6A, 0x3E, 0x5E, 0x07, 0x61, 0x56, 0x57, 0x3F, 0x8A };
        static byte[] WADMagic = new byte[8] { 0x00, 0x00, 0x00, 0x20, 0x49, 0x73, 0x00, 0x00 };
        static byte[] CRL_LEN = new byte[4] { 0x00, 0x00, 0x00, 0x00 };
        static byte[] TIKSIZE_CONST = new byte[4] { 0x00, 0x00, 0x02, 0xA4 };
        static byte[] FOOTER_LEN = new byte[4] { 0x00, 0x00, 0x00, 0x00 };

        public Wad(byte[] tmd, byte[] ticket, List<byte[]> contents)
        {
            this.tmd = tmd;
            this.ticket = ticket;
            this.contents = contents;

            ExtractCerts(tmd);
            ExtractCerts(ticket);

            if (!Convert.ToBase64String(ComputeSHA(cert_CA)).Equals(Convert.ToBase64String(Wad.cert_CA_sha1))
                || !Convert.ToBase64String(ComputeSHA(cert_CACP)).Equals(Convert.ToBase64String(Wad.cert_CACP_sha1))
                || !Convert.ToBase64String(ComputeSHA(cert_CAXS)).Equals(Convert.ToBase64String(Wad.cert_CAXS_sha1)))
                throw new Exception();

            List<byte> tempCert = new List<byte>();
            tempCert.AddRange(cert_CA);
            tempCert.AddRange(cert_CACP);
            tempCert.AddRange(cert_CAXS);
            cert = tempCert.ToArray();
        }

        static private void ExtractCerts(byte[] buffer)
        {
            FindElement(buffer, cert_CA, Wad.cert_CA_sha1);
            FindElement(buffer, cert_CACP, Wad.cert_CACP_sha1);
            FindElement(buffer, cert_CAXS, Wad.cert_CAXS_sha1);
        }

        static private void FindElement(byte[] input, byte[] output, byte[] hash)
        {
            int position = 0;
            //if not already found
            while (!Convert.ToBase64String(ComputeSHA(output)).Equals(Convert.ToBase64String(hash)))
            {
                if (input.Length - position < output.Length)
                    break;

                for (int index = 0; index < output.Length; index++)
                    output[index] = input[index + position];

                position++;
            }
        }

        static public byte[] ComputeSHA(byte[] data)
        {
            SHA1 sha = new SHA1CryptoServiceProvider();
            // This is one implementation of the abstract class SHA1.
            return sha.ComputeHash(data);
        }
		
        private byte[] ToByteArray(Int32 value)
        {
            byte[] array = new byte[4];

            for (int index = 0; index < array.Length; index++)
                array[array.Length - index - 1] = (byte)(value >> (8 * index));

            return array;
        }

        private long NextBoudary(long position, uint boundary)
        {
            long dif = position % boundary;
            return dif == 0 ? position : position + (boundary - dif);
        }

        public void Pack(string file)
        {
            using (FileStream wadfs = File.Create(file))
            {
                // Write initial part of header (WADType)
                wadfs.Write(Wad.WADMagic, 0, Wad.WADMagic.Length);

                // Write CertChainLength
                wadfs.Write(ToByteArray(cert.Length), 0, 4);

                // Write res
                wadfs.Write(Wad.CRL_LEN, 0, Wad.CRL_LEN.Length);

                // Write ticketsize
                wadfs.Write(Wad.TIKSIZE_CONST, 0, Wad.TIKSIZE_CONST.Length);
                
                // Write tmdsize
                wadfs.Write(ToByteArray(contents.Count * 36 + 484), 0, 4);

                // Write data size
                wadfs.Write(ToByteArray(contents.Sum(array => array.Length)), 0, 4);

                //write footer len
                wadfs.Write(Wad.FOOTER_LEN, 0, Wad.FOOTER_LEN.Length);

                //align to 0x40
                wadfs.Seek(NextBoudary(wadfs.Position, 64), SeekOrigin.Begin);

                // Write cert[]
                wadfs.Write(cert, 0, cert.Length);
                wadfs.Seek(NextBoudary(wadfs.Position, 64), SeekOrigin.Begin);

                // Write ticket at this point...
                wadfs.Write(ticket, 0, TicketSize);
                wadfs.Seek(NextBoudary(wadfs.Position, 64), SeekOrigin.Begin);

                // Write TMD at this point...
                wadfs.Write(tmd, 0, contents.Count * 36 + 484);
                wadfs.Seek(NextBoudary(wadfs.Position, 64), SeekOrigin.Begin);

                // Add the individual contents
                foreach(byte[] content in contents)
                {

                    wadfs.Write(content, 0, content.Length);
                    wadfs.Seek(NextBoudary(wadfs.Position, 64), SeekOrigin.Begin);
                }
            }
        }
    }
}
