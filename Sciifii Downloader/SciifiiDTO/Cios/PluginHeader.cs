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
        public Int32 Type { get; set; }

        [XmlAttribute(AttributeName = "vaddr")]
        public String VirtualAddress { get; set; }

        [XmlAttribute(AttributeName = "paddr")]
        public String PhysicalAddress { get; set; }

        [XmlAttribute(AttributeName = "flag")]
        public String Flag { get; set; }

        [XmlAttribute(AttributeName = "align")]
        public Int32 Align { get; set; }

        public PluginHeader(int type, 
            string virtualAddress, 
            string physicalAddress, 
            string flag, 
            int align)
        {
            this.Type = type;
            this.VirtualAddress = virtualAddress;
            this.PhysicalAddress = physicalAddress;
            this.Flag = flag;
            this.Align = align;
        }
    }
}
