using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("SimplePatch")]
    public class SimplePatch : Patch
    {
        [XmlAttribute(AttributeName = "pattern")]
        public string Pattern { get; set; }

        [XmlAttribute(AttributeName = "value")]
        public string Value { get; set; }
    }
}
