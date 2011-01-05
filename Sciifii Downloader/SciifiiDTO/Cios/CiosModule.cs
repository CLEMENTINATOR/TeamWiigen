using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("ciosModule")]
    public class CiosModule
    {
        [XmlAttribute(AttributeName = "file")]
        public String File { get; set; }

        [XmlAttribute(AttributeName = "position")]
        public UInt16 Position { get; set; }

        public CiosModule(string file, ushort position)
        {
            this.File = file;
            this.Position = position;
        }
    }
}
