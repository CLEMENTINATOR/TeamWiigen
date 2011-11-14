using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using Sciifii.DTO.Menus;

namespace Sciifii.DTO
{
    [Serializable]
    [XmlType("menu")]
    public class Menu
    {
        [XmlAttribute("id")]
        public string Id { get; set; }

        [XmlAttribute("title")]
        public string Title { get; set; }

        [XmlAttribute("message")]
        public string Message { get; set; }

        [XmlElement("separatorMenuItem", typeof(SeparatorMenuItem))]
        [XmlElement("navigationMenuItem", typeof(NavigationMenuItem))]
        [XmlElement("exitMenuItem", typeof(ExitMenuItem))]
        [XmlElement("modeMenuItem", typeof(ModeMenuItem))]
        [XmlElement("previousMenuItem", typeof(PreviousMenuItem))]
        [XmlElement("switchMenuItem", typeof(SwitchMenuItem))]
        [XmlElement("startMenuItem", typeof(StartMenuItem))]
        public List<MenuItem> Items { get; set; }

        public Menu()
        {
            Items = new List<MenuItem>();
        }
    }
}
