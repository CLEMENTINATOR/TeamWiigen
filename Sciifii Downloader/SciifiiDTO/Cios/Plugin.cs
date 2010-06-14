using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("ciosPlugin")]
    public class Plugin
    {
        public Plugin()
        { }

        [XmlAttribute(AttributeName = "dest")]
        public String ModuleName { get; set; }

        [XmlAttribute(AttributeName = "file")]
        public String File { get; set; }

        [XmlAttribute(AttributeName = "segment")]
        public UInt16 Segment { get; set; }

        [XmlElement(ElementName = "header")]
        public PluginHeader Header { get; set; }

        [XmlElement(ElementName = "handle")]
        public List<PluginHandle> Handles { get; set; }
    }
}
