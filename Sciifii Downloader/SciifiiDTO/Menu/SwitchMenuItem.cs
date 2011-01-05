using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "switchMenuItem")]
    public class SwitchMenuItem
    {
        [XmlAttribute(AttributeName = "name")]
        public String Name { get; set; }

        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "hidden")]
        public Boolean Hidden { get; set; }

        public SwitchMenuItem(string name, string text, bool hidden)
        {
            this.Name = name;
            this.Text = text;
            this.Hidden = hidden;
        }
    }
}
