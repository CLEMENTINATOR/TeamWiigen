using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO
{
    [Serializable]
    public enum LogType
    {
        [XmlEnum("file")]
        File,
        [XmlEnum("gecko")]
        Gecko,
        [XmlEnum("web")]
        Web
    }

    [Serializable]
    public enum LogCategory
    {
        [XmlEnum("error")]
        Error,
        [XmlEnum("warning")]
        Warning,
        [XmlEnum("info")]
        Info,
        [XmlEnum("debug")]
        Debug,
        [XmlEnum("all")]
        All
    }

    [Serializable]
    [XmlType("log")]
    public class Log
    {
        [XmlAttribute("type")]
        public LogType Type { get; set; }

        [XmlAttribute("category")]
        public LogCategory Category { get; set; }

        [XmlAttribute("path")]
        public string Path { get; set; }

        [XmlAttribute("url")]
        public string Url { get; set; }

        public Log()
        {
            Category = LogCategory.All;
        }
    }
}
