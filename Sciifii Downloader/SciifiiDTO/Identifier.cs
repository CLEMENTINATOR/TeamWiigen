using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "Identifier")]
    public class Identifier : Step
    {
        [XmlAttribute(AttributeName = "user")]
        public UInt32 userId { get; set; }

        public Identifier()
        {

        }
    }
}
