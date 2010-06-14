using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using SciifiiDTO.Cios;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType("CiosInstaller")]
    public class CiosInstaller : Step
    {
        [XmlAttribute(AttributeName = "source")]
        public UInt32 Source { get; set; }

        [XmlAttribute(AttributeName = "revision")]
        public UInt32 SourceRevision { get; set; }

        [XmlAttribute(AttributeName = "slot")]
        public UInt32 DestinationSlot { get; set; }

        [XmlAttribute(AttributeName = "ciosRevision")]
        public UInt32 DestinationRevision { get; set; }

        [XmlArrayItem(ElementName = "module", Type = typeof(CiosModule))]
        [XmlArray(ElementName = "modules")]
        public List<CiosModule> Modules { get; set; }

        [XmlArrayItem(ElementName = "plugin", Type = typeof(Plugin))]
        [XmlArray(ElementName = "plugins")]
        public List<Plugin> Plugins { get; set; }

        [XmlArrayItem(ElementName = "prebuild", Type = typeof(PreBuildPatch))]
        [XmlArrayItem(ElementName = "SimplePatch", Type = typeof(SimplePatch))]
        [XmlArray(ElementName = "patches")]
        public List<Patch> Patches { get; set; }

        public CiosInstaller()
        {
            Plugins = new List<Plugin>();
            Modules = new List<CiosModule>();
        }
    }
}
