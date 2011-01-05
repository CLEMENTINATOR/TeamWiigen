using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    public enum FST_Type
    {
        [XmlEnum("file")]
        File,
        [XmlEnum("folder")]
        Folder,
    }

    public enum FST_Action
    {
        [XmlEnum("move")]
        Move,
        [XmlEnum("copy")]
        Copy,
        [XmlEnum("delete")]
        Delete,
    }

    [Serializable]
    [XmlType(TypeName = "FileSystemTask")]
    public class FileSystemTask : Step
    {
        [XmlAttribute(AttributeName = "target")]
        public String Target { get; set; }

        [XmlAttribute(AttributeName = "destination")]
        public String Destination { get; set; }

        [XmlAttribute(AttributeName = "recursive")]
        public Boolean Recursive { get; set; }

        [XmlAttribute(AttributeName = "type")]
        public FST_Type Type { get; set; }

        [XmlAttribute(AttributeName = "action")]
        public FST_Action Action { get; set; }

        public FileSystemTask(string target, 
            string destination,
            bool recursive,
            FST_Type type,
            FST_Action action)
        {
            this.Target = target;
            this.Destination = destination;
            this.Recursive = recursive;
            this.Type = type;
            this.Action = action;
        }
    }
}
