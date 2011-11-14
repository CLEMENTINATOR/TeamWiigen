using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    [XmlType("switchMenuItem")]
    public class SwitchMenuItem : MenuItem
    {
        [XmlAttribute("name")]
        public String Key { get; set; }

        [XmlAttribute("text")]
        public String Text { get; set; }
    }
}
