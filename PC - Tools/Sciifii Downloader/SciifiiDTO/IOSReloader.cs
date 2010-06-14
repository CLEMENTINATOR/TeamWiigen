using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "IOSReloader")]
    public class IOSReloader : Step
    {
        [XmlAttribute(AttributeName = "id")]
        public UInt32 Id { get; set; }

        [XmlAttribute(AttributeName = "user")]
        public Int32 UserId { get; set; }

        public IOSReloader()
        {
            UserId = -1;
        }
    }
}
