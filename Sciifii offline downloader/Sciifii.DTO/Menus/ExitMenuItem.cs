using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    [XmlType("exitMenuItem")]
    public class ExitMenuItem : MenuItem
    {
        [XmlAttribute("text")]
        public string Text { get; set; }
    }
}
