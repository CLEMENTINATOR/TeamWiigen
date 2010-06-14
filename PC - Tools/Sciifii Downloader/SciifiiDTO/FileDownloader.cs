using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "FileDownloader")]
    public class FileDownloader : Step
    {
        [XmlAttribute(AttributeName = "file")]
        public string FileKey { get; set; }
    }
}
