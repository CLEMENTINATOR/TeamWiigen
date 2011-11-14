using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps.Patches
{
    [Serializable]
    [XmlType("module")]
    public class Module
    {
        [XmlAttribute("file")]
        public string SourceFile { get; set; }

        [XmlAttribute("position")]
        public int Position { get; set; }

        public Module()
        {
            Position = -1;
        }
    }
}
