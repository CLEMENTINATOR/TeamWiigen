using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO
{
    [Serializable]
    [XmlType("file")]
    public class File
    {
        [XmlAttribute("key")]
        public string Key { get; set; }

        [XmlAttribute("url")]
        public string Url { get; set; }

        [XmlAttribute("sha1")]
        public string Sha1Url { get; set; }

        [XmlAttribute("path")]
        public string Path { get; set; }
    }
}
