using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Log
{
    [Serializable]
    [XmlType(TypeName = "log")]
    public class Log
    {
        [XmlAttribute(AttributeName = "type")]
        public LogType Type { get; set; }

        [XmlAttribute(AttributeName = "category")]
        public LogCategory Category { get; set; }

        [XmlAttribute(AttributeName = "path")]
        public String Path { get; set; }

        [XmlAttribute(AttributeName = "url")]
        public String Url { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Log()
        { }

        public Log(LogType type,
            LogCategory category,
            string path,
            string url)
        {
            this.Type = type;
            this.Category = category;
            this.Path = path;
            this.Url = url;
        }
    }
}
