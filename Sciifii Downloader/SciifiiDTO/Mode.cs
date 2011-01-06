using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "mode")]
    public class Mode
    {
        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "flag")]
        public String Flag { get; set; }

        [XmlAttribute(AttributeName = "options")]
        public String OptionsString { get; set; }

        [XmlIgnore]
        public List<String> Options { get { return OptionsString.Split('|').ToList(); } }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Mode()
        { }
        
        public Mode(string text, string flag, string optionsString)
        {
            this.Text = text;
            this.Flag = flag;
            this.OptionsString = optionsString;
        }
    }
}
