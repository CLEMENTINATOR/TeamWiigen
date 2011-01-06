using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "CompositeInstaller")]
    public class CompositeInstaller : Step
    {
        [XmlElement(ElementName = "CiosInstaller", Type = typeof(CiosInstaller))]
        [XmlElement(ElementName = "MemoryPatcher", Type = typeof(MemoryPatcher))]
        [XmlElement(ElementName = "CorpInstaller", Type = typeof(CiosCorp))]
        [XmlElement(ElementName = "Title", Type = typeof(TitleInstaller))]
        [XmlElement(ElementName = "CompositeInstaller", Type = typeof(CompositeInstaller))]
        [XmlElement(ElementName = "FileDownloader", Type = typeof(FileDownloader))]
        [XmlElement(ElementName = "FileSystem", Type = typeof(FileSystemTask))]
        [XmlElement(ElementName = "WadBatchInstaller", Type = typeof(WadBatchInstaller))]
        [XmlElement(ElementName = "TitleDowngrader", Type = typeof(TitleDowngrader))]
        [XmlElement(ElementName = "IOSReloader", Type = typeof(IOSReloader))]
        [XmlElement(ElementName = "Preloader", Type = typeof(Preloader))]
        public List<Step> Steps { get; set; }

        [XmlAttribute(AttributeName = "name")]
        public String Name { get; set; }

        [XmlIgnore]
        public Int32 StepsFullCount
        {
            get
            {
                int nbSteps = 0;

                foreach (Step s in Steps)
                    if (s is CompositeInstaller)
                    {
                        nbSteps += (s as CompositeInstaller).StepsFullCount;
                    }
                    else
                        nbSteps++;

                return nbSteps;
            }
        }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public CompositeInstaller()
        {
            this.Steps = new List<Step>();
        }

        public CompositeInstaller(List<Step> steps, string name)
        {
            this.Steps = steps;
            this.Name = name;
        }
    }
}
