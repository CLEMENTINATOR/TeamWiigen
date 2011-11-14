using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    [Serializable]
    [XmlType("CompositeInstaller")]
    public class CompositeInstaller : BaseStep
    {
        [XmlAttribute("name")]
        public string Name { get; set; }

        [XmlElement("MemoryPatcher", typeof(MemoryPatcher))]
        [XmlElement("CiosInstaller", typeof(CiosInstaller))]
        [XmlElement("CompositeInstaller", typeof(CompositeInstaller))]
        [XmlElement("Title", typeof(Title))]
        [XmlElement("FileSystem", typeof(FileSystem))]
        [XmlElement("Preloader", typeof(Preloader))]
        [XmlElement("FileDownloader", typeof(FileDownloader))]
        public List<BaseStep> Steps { get; set; }

        public CompositeInstaller()
        {
            Steps = new List<BaseStep>();
        }

        [XmlIgnore]
        public int StepsFullCount
        {
            get
            {
                int normalSteps = Steps.Where(s => !(s is CompositeInstaller)).Count();
                foreach (CompositeInstaller installer in Steps.Where(s => s is CompositeInstaller))
                    normalSteps += installer.StepsFullCount;

                return normalSteps;
            }
        }
    }
}
