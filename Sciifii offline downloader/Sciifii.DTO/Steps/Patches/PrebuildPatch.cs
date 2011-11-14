using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps.Patches
{
    [Serializable]
    [XmlType("prebuild")]
    public class PrebuildPatch : BasePatch
    {
        [XmlAttribute("name")]
        public string Name { get; set; }
    }
}
