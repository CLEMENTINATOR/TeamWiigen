using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "modeMenuItem")]
    public class ModeMenuItem
    {
        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "switches")]
        public String Switches { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public ModeMenuItem()
        { }

        public ModeMenuItem(string text, string switches)
        {
            this.Text = text;
            this.Switches = switches;
        }
    }
}
