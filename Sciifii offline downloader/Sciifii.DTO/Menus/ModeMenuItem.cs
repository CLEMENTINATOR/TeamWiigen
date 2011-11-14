using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    [XmlType("modeMenuItem")]
    public class ModeMenuItem : MenuItem
    {
        [XmlAttribute("text")]
        public string Text { get; set; }

        [XmlAttribute("switches")]
        public string SwitchString { get; set; }

        [XmlIgnore]
        public List<string> Switches
        {
            get
            {
                return SwitchString.Split('|').ToList();
            }
        }
    }
}
