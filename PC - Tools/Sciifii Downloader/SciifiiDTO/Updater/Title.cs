using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Updater
{
    [Serializable]
    [XmlType("title")]
    public class Title
    {
        [XmlAttribute(AttributeName = "id")]
        public String TitleId { get; set; }

        [XmlAttribute(AttributeName = "revision")]
        public UInt16 TitleRevision { get; set; }

        [XmlAttribute(AttributeName = "region")]
        public Regions Region { get; set; }

        public Title()
        {
            Region = Regions.ALL;
        }
    }
}
