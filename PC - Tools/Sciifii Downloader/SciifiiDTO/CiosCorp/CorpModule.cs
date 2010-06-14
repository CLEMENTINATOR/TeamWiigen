using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Corp
{
    [Serializable]
    [XmlType("corpModule")]
    public class CorpModule
    {
        [XmlAttribute(AttributeName = "type")]
        public string ModuleName { get; set; }

        [XmlAttribute(AttributeName = "name")]
        public string Name { get; set; }

        [XmlAttribute(AttributeName = "file")]
        public string File { get; set; }
    }
}
