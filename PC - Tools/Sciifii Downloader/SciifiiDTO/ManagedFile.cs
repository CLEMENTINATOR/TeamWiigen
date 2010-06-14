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
        public string Key { get; set; }

        [XmlAttribute(AttributeName = "url")]
        public String Url { get; set; }

        [XmlAttribute(AttributeName = "sha1")]
        public string ShaUrl { get; set; }

        [XmlAttribute(AttributeName = "path")]
        public string FilePath { get; set; }
    }
}
