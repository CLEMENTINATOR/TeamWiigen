using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlRoot(Namespace = "", IsNullable = false, ElementName = "sciifii")]
    public class SciifiiConfiguration
    {
        [XmlIgnore]
        public Regions SelectedRegion { get; set; }

        [XmlAttribute(AttributeName = "version")]
        public UInt16 Version { get; set; }

        [XmlAttribute(AttributeName = "MenuMessage")]
        public String MenuMessage { get; set; }

        [XmlAttribute(AttributeName = "themeDirectory")]
        public String ThemeDirectory { get; set; }

        [XmlAttribute(AttributeName = "AllowAdvancedMode")]
        public bool AllowAdvancedMode { get; set; }

        [XmlAttribute(AttributeName = "workingDirectory")]
        public String workingDirectory { get; set; }

        [XmlElement(ElementName = "Disclaimer")]
        public String Disclaimer { get; set; }

        [XmlArray(ElementName = "files")]
        public List<ManagedFile> ManagedFiles { get; set; }

        [XmlArray(ElementName = "modes")]
        public List<Mode> Modes { get; set; }

        [XmlArray(ElementName = "menus")]
        public List<Menu.Menu> Menus { get; set; }

        [XmlArray(ElementName = "options")]
        public List<Option> Options { get; set; }

        [XmlArrayItem(ElementName = "CiosInstaller", Type = typeof(CiosInstaller))]
        [XmlArrayItem(ElementName = "MemoryPatcher", Type = typeof(MemoryPatcher))]
        [XmlArrayItem(ElementName = "CorpInstaller", Type = typeof(CiosCorp))]
        [XmlArrayItem(ElementName = "Title", Type = typeof(TitleInstaller))]
        [XmlArrayItem(ElementName = "CompositeInstaller", Type = typeof(CompositeInstaller))]
        [XmlArrayItem(ElementName = "FileDownloader", Type = typeof(FileDownloader))]
        [XmlArrayItem(ElementName = "FileSystem", Type = typeof(FileSystemTask))]
        [XmlArrayItem(ElementName = "WadBatchInstaller", Type = typeof(WadBatchInstaller))]
        [XmlArrayItem(ElementName = "TitleDowngrader", Type = typeof(TitleDowngrader))]
        [XmlArrayItem(ElementName = "IOSReloader", Type = typeof(IOSReloader))]
        [XmlArray(ElementName = "steps")]
        public List<Step> Steps { get; set; }

        /*public SciifiiConfiguration()
        {
            AllowAdvancedMode = true;
            workingDirectory = "sd:/sciifii/temp";
            ManagedFiles = new List<ManagedFile>();
            Modes = new List<Mode>();
            Steps = new List<Step>();
        }*/
    }
}
