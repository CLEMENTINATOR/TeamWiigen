using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "startMenuItem")]
    public class StartMenuItem
    {
        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "saveOptions")]
        public Boolean SaveOptions { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public StartMenuItem()
        { }
        
        public StartMenuItem(string text, bool saveOptions)
        {
            this.Text = text;
            this.SaveOptions = saveOptions;
        }
    }
}
