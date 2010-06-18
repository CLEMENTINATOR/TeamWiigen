using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Corp
{
    [Serializable]
    [XmlType("item")]
    public class CorpItem
    {
        [XmlAttribute(AttributeName = "slot")]
        public string Slot { get; set; }

        [XmlAttribute(AttributeName = "source")]
        public string Source { get; set; }

        [XmlAttribute(AttributeName = "revision")]
        public UInt16 TitleRevision { get; set; }

        [XmlAttribute(AttributeName = "identifyPatch")]
        public Boolean IdentifyPatch { get; set; }

        [XmlAttribute(AttributeName = "nandPatch")]
        public Boolean NandPatch { get; set; }

        [XmlAttribute(AttributeName = "kkPatch")]
        public Boolean KoreanPatch { get; set; }

        [XmlAttribute(AttributeName = "localOnly")]
        public Boolean LocalOnly { get; set; }

        [XmlAttribute(AttributeName = "modules")]
        public string ModulesString { get; set; }

        [XmlIgnore]
        public List<String> Modules
        {
            get { return ModulesString.Split('|').ToList(); }
        }
    }
}
