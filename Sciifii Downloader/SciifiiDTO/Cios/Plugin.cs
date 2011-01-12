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
        [XmlAttribute(AttributeName = "dest")]
        public String ModuleName { get; set; }

        [XmlAttribute(AttributeName = "file")]
        public String File { get; set; }

        [XmlAttribute(AttributeName = "offset")]
        public UInt32 Offset { get; set; }

        [XmlAttribute(AttributeName = "bss")]
        public UInt32 Bss { get; set; }

        [XmlAttribute(AttributeName = "segment")]
        public UInt16 Segment { get; set; }

        [XmlElement(ElementName = "header")]
        public PluginHeader Header { get; set; }

        [XmlElement(ElementName = "handle")]
        public List<PluginHandle> Handles { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Plugin()
        {
            this.Handles = new List<PluginHandle>();
        }
        
        public Plugin(string moduleName, 
            string file,
            uint offset,
            uint bss,
            ushort segment, 
            PluginHeader header, 
            List<PluginHandle> handles)
        {
            this.ModuleName = moduleName;
            this.File = file;
            this.Offset = offset;
            this.Bss = bss;
            this.Segment = segment;
            this.Header = header;
            this.Handles = handles;
        }
    }
}
