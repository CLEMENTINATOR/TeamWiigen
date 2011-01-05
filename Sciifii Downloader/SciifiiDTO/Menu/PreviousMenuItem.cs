using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "previousMenuItem")]
    public class PreviousMenuItem
    {
        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "saveOptions")]
        public Boolean SaveOptions { get; set; }

        public PreviousMenuItem(string text, bool saveOptions)
        {
            this.Text = text;
            this.SaveOptions = saveOptions;
        }
    }
}
