using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "exitMenuItem")]
    public class ExitMenuItem
    {
        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        public ExitMenuItem(string text)
        {
            this.Text = text;
        }
    }
}
