using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using Sciifii.DTO.Steps.Patches;

namespace Sciifii.DTO.Steps
{
    [Serializable]
    [XmlType("CiosInstaller")]
    public class CiosInstaller : BaseStep
    {
        private ushort iosRevision;
        [XmlAttribute("revision")]
        public ushort IosRevision
        {
            get { return iosRevision; }
            set
            {
                iosRevision = value;
                if (CiosRevision == 0)
                    CiosRevision = value;
            }
        }

        private uint iosVersion;
        [XmlAttribute("source")]
        public uint IosVersion
        {
            get { return iosVersion; }
            set
            {
                iosVersion = value;
                if (CiosVersion == 0)
                    CiosVersion = value;
            }
        }

        [XmlAttribute("ciosRevision")]
        public ushort CiosRevision { get; set; }

        [XmlAttribute("slot")]
        public uint CiosVersion { get; set; }

        [XmlAttribute("banner")]
        public string BannerSourceFile { get; set; }

        [XmlArray("modules")]
        [XmlArrayItem("module", typeof(Module))]
        public List<Module> Modules { get; set; }

        [XmlArray("patches")]
        [XmlArrayItem("prebuild", typeof(PrebuildPatch))]
        [XmlArrayItem("SimplePatch", typeof(SimplePatch))]
        public List<BasePatch> Patches { get; set; }

        public CiosInstaller()
        {
            Modules = new List<Module>();
            Patches = new List<BasePatch>();
            CiosVersion = 0;
            CiosRevision = 0;
        }
    }
}
