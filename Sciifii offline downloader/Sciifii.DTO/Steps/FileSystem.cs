using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    public enum FileSystemAction
    {
        [XmlEnum("move")]
        Move,
        [XmlEnum("copy")]
        Copy,
        [XmlEnum("delete")]
        Delete
    }

    public enum FileSystemType
    {
        [XmlEnum("file")]
        File,
        [XmlEnum("folder")]
        Folder
    }

    [Serializable]
    [XmlType("FileSystem")]
    public class FileSystem : BaseStep
    {
        [XmlAttribute("target")]
        public string Target { get; set; }


        [XmlAttribute("destination")]
        public string Destination { get; set; }

        [XmlAttribute("recursive")]
        public bool Recusrsive { get; set; }

        [XmlAttribute("type")]
        public FileSystemType Type { get; set; }

        [XmlAttribute("action")]
        public FileSystemAction Action { get; set; }
    }
}
