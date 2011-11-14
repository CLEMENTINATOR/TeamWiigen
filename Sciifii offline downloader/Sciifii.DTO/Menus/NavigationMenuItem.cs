using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    [XmlType("navigationMenuItem")]
    public class NavigationMenuItem : MenuItem
    {
        [XmlAttribute("text")]
        public string Text { get; set; }

        [XmlAttribute("menuId")]
        public string MenuId { get; set; }

        [XmlAttribute("saveOptions")]
        public bool SaveOptions { get; set; }
    }
}
