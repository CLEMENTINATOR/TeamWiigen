using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "TitleDowngrader")]
    public class TitleDowngrader : Step
    {
        [XmlAttribute(AttributeName = "id")]
        public String Id { get; set; }

        [XmlAttribute(AttributeName = "revision")]
        public UInt16 Revision { get; set; }
    }
}
