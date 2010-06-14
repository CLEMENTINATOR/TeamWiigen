using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("header")]
    public class PluginHeader
    {
        [XmlAttribute(AttributeName = "type")]
        public int Type { get; set; }

        [XmlAttribute(AttributeName = "vaddr")]
        public string VirtualAddress { get; set; }

        [XmlAttribute(AttributeName = "paddr")]
        public String PhisicalAddress { get; set; }

        [XmlAttribute(AttributeName = "flag")]
        public String Flag { get; set; }

        [XmlAttribute(AttributeName = "align")]
        public int Align { get; set; }
    }
}
