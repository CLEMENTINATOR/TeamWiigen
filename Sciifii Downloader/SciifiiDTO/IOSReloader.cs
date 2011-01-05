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

        public IOSReloader(uint id)
        {
            this.Id = id;
        }
    }
}
