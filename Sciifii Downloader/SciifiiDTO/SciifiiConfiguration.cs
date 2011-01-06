﻿using System;
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
        public Boolean AllowAdvancedMode { get; set; }

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

        /// <summary>
        /// Need by serialization
        /// </summary>
        public SciifiiConfiguration()
        {
            workingDirectory = "sd:/sciifii";
            this.ManagedFiles = new List<ManagedFile>();
            this.Modes = new List<Mode>();
            this.Menus = new List<Menu.Menu>();
            this.Options = new List<Option>();
            this.Steps = new List<Step>();
        }
        
        public SciifiiConfiguration(ushort version,
            string menuMessage,
            string themeDirectory,
            string workingDirectory,
            string disclaimer,
            List<ManagedFile> managedFiles,
            List<Mode> modes,
            List<Menu.Menu> menus,
            List<Option> options,
            List<Step> steps)
        {
            this.Version = version;
            this.MenuMessage = menuMessage;
            this.ThemeDirectory = themeDirectory;
            this.workingDirectory = workingDirectory;
            this.Disclaimer = disclaimer;
            this.ManagedFiles = managedFiles;
            this.Modes = modes;
            this.Menus = menus;
            this.Options = options;
            this.Steps = steps;
        }
    }
}
