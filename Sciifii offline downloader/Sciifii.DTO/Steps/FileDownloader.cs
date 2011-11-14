using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    [Serializable]
    [XmlType("FileDownloader")]
    public class FileDownloader : BaseStep
    {
        [XmlAttribute("file")]
        public string File { get; set; }
    }
}
