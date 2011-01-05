using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "file")]
    public class ManagedFile
    {
        [XmlAttribute(AttributeName = "key")]
        public String Key { get; set; }

        [XmlAttribute(AttributeName = "url")]
        public String Url { get; set; }

        [XmlAttribute(AttributeName = "sha1")]
        public String ShaUrl { get; set; }

        [XmlAttribute(AttributeName = "path")]
        public String FilePath { get; set; }

        public ManagedFile(string key, string url, string shaUrl, string filePath)
        {
            this.Key = key;
            this.Url = url;
            this.ShaUrl = shaUrl;
            this.FilePath = filePath;
        }
    }
}
