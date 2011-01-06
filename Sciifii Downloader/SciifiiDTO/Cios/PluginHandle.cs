using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("handle")]
    public class PluginHandle
    {
        [XmlAttribute(AttributeName = "name")]
        public String Name { get; set; }

        [XmlAttribute(AttributeName = "pattern")]
        public String Pattern { get; set; }

        [XmlAttribute(AttributeName = "value")]
        public String Value { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public PluginHandle()
        { }
        
        public PluginHandle(string name, string pattern, string value)
        {
            this.Name = name;
            this.Pattern = pattern;
            this.Value = value;
        }
    }
}
