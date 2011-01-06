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
        public UInt16 SourceRevision { get; set; }

        [XmlAttribute(AttributeName = "slot")]
        public UInt32 DestinationSlot { get; set; }

        [XmlAttribute(AttributeName = "ciosRevision")]
        public Int32 DestinationRevision { get; set; }

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

        /// <summary>
        /// Need by serialization
        /// </summary>
        public CiosInstaller()
        {
            this.Modules = new List<CiosModule>();
            this.Plugins = new List<Plugin>();
            this.Patches = new List<Patch>();
        }
        
        public CiosInstaller(uint source, 
            ushort sourceRevision, 
            uint destinationSlot, 
            int destinationRevision, 
            List<CiosModule> modules, 
            List<Plugin> plugins,
            List<Patch> patches)
        {
            this.Source = source;
            this.SourceRevision = sourceRevision;
            this.DestinationSlot = destinationSlot;
            this.DestinationRevision = DestinationRevision;
            this.Modules = modules;
            this.Plugins = plugins;
            this.Patches = patches;
        }
    }
}
