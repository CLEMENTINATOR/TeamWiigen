using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net;
using System.Security.Cryptography;

namespace SciifiiBusiness
{
    public class FileDownloader
    {
        public static void Download(string key, string url, string folder, string workingDirectory)
        {
            Download(key, url, String.Empty, String.Empty, folder, workingDirectory);
        }

        public static void Download(string key, string url, string sha1, string folder, string workingDirectory)
        {
            Download(key, url, sha1, String.Empty, folder, workingDirectory);
        }

        public static void Download(string key, string url, string sha1, string path, string folder, string workingDirectory)
        {
            if (string.IsNullOrEmpty(url))
                return;

            string filePath = GetRealPath(key, path, folder, workingDirectory);

            if (File.Exists(filePath))
                return;
           DirectoryInfo di= Directory.GetParent(filePath);
           di.Create();

            WebClient client = new WebClient();
            client.Proxy = WebRequest.GetSystemWebProxy();
            client.UseDefaultCredentials = true;
            Byte[] fileData = client.DownloadData(url);
            client.Dispose();

            if (!String.IsNullOrEmpty(sha1))
                if (!ValidateSha1(fileData, sha1))
                    throw new Exception("Error downloading file.");


            File.WriteAllBytes(filePath, fileData);
        }

        private static bool ValidateSha1(byte[] fileData, string sha1)
        {
            WebClient client = new WebClient();
            client.Proxy = WebRequest.GetSystemWebProxy();
            client.UseDefaultCredentials = true;
            Byte[] hash = client.DownloadData(sha1);
            client.Dispose();

            SHA1Managed crypto = new SHA1Managed();
            Byte[] cHash = crypto.ComputeHash(fileData);

            for (int index = 0; index < hash.Length; index++)
                if (hash[index] != cHash[index])
                    return false;

            return true;
        }

        private static string GetRealPath(string key, string path, string folder, string workingDirectory)
        {
            string sdDirectory;
            string device;
            if (!String.IsNullOrEmpty(path))
            {
                sdDirectory = path.Substring(path.IndexOf('/'));
                device = path.Substring(0, path.IndexOf('/') - 1);
            }
            else
            {
                device = workingDirectory + "/" + key;
                sdDirectory = device.Substring(device.IndexOf('/'));
                device = device.Substring(0, device.IndexOf('/') - 1);
            }

            string realDirectory = folder + "\\"  + sdDirectory;
            realDirectory = realDirectory.Replace("/", "\\");

            while (realDirectory.Contains("\\\\"))
            {
                realDirectory = realDirectory.Replace("\\\\", "\\");
            }

            return realDirectory;
        }
    }
}
