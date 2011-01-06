using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "option")]
    public class Option
    {
        [XmlAttribute(AttributeName = "name")]
        public String Name { get; set; }

        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "hidden")]
        public Boolean Hidden { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Option()
        { }
        
        public Option(string name, string text, bool hidden)
        {
            this.Name = name;
            this.Text = text;
            this.Hidden = hidden;
        }
    }
}
