using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    [XmlType("separatorMenuItem")]
    public class SeparatorMenuItem : MenuItem
    {
        [XmlAttribute("char")]
        public string SeparatorCharacter { get; set; }

        [XmlIgnore]
        public override bool BreakBefore
        {
            get
            {
                return true;
            }
        }

        [XmlIgnore]
        public override bool BreakAfter
        {
            get
            {
                return true;
            }
        }
    }
}
