using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using Sciifii.DTO.Steps.Patches;

namespace Sciifii.DTO.Steps
{
    [Serializable]
    [XmlType("MemoryPatcher")]
    public class MemoryPatcher : BaseStep
    {
        [XmlElement("patch", typeof(SimplePatch))]
        public List<SimplePatch> Patches { get; set; }

        public MemoryPatcher()
        {
            Patches = new List<SimplePatch>();
        }
    }
}
