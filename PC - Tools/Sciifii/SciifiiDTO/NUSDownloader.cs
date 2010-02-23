using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;

namespace SciifiiDTO
{
    public class NUSDownloader
    {
        WebClient nus;
        UInt64 titleId;
        UInt16 revision;

        string wadFile;

        byte[] tmd;
        byte[] ticket;

        private NUSDownloader(UInt64 titleId, UInt16 revision)
        {
            nus = new WebClient();
            nus.Headers.Add("User-Agent", "wii libnup/1.0");
            nus.Proxy = WebRequest.GetSystemWebProxy();
            nus.UseDefaultCredentials = true;

            UInt32 titleType = (UInt32)(titleId >> 32);
            UInt32 id = (UInt32)titleId;

            //Si IOS
            if (titleType == 1)
            {
                wadFile = "IOS" + id;
                if (revision > 0)
                    wadFile += "-64-v" + revision;
                wadFile += ".wad";
            }
            else
            {
                wadFile = titleType.ToString("x8") + "-" + id.ToString("x8");
                if (revision > 0)
                    wadFile += "v" + revision;
                wadFile += ".wad";
            }

            this.titleId = titleId;
            this.revision = revision;
        }

        private byte[] DownloadFile(string filename)
        {
            // Create NUS URL...
            string nusfileurl = "http://nus.cdn.shop.wii.com/ccs/download/" + titleId.ToString("x16") + Path.AltDirectorySeparatorChar.ToString() + filename;

            // Download NUS file...
            return nus.DownloadData(nusfileurl);
        }

        UInt16 ExtractU16(byte[] buffer, Int64 offset)
        {
            UInt16 value = 0;

            for (short i = 0; i < 2; i++)
            {
                value = (ushort)(value * 0xFF);
                value += buffer[offset + i];
            }

            return value;
        }

        UInt32 ExtractU32(byte[] buffer, Int64 offset)
        {
            UInt32 value = 0;

            for (short i = 0; i < 4; i++)
            {
                value = (ushort)(value * 0xFF);
                value += buffer[offset + i];
            }

            return value;
        }

        public void Download(string folder)
        {
            string file = folder + "\\" + wadFile;

            if (File.Exists(file))
                return;

            tmd = DownloadFile(revision == 0 ? "tmd" : String.Format("tmd.{0}", revision));
            ticket = DownloadFile("cetk");
            UInt16 contentCount = ExtractU16(tmd, 0x1DE);
            List<byte[]> contents = new List<byte[]>();

            for (UInt16 contentIndex = 0; contentIndex < contentCount; contentIndex++)
            {
                UInt32 id = ExtractU32(tmd, 0x1E4 + 36 * contentIndex);
                contents.Add(DownloadFile(id.ToString("x8")));
            }


            Wad w = new Wad(tmd, ticket, contents);
            w.Pack(file);
        }

        public static void DownloadWad(UInt64 titleId, UInt16 revision, string folder)
        {
            NUSDownloader d = new NUSDownloader(titleId, revision);
            d.Download(folder);
        }
    }
}
