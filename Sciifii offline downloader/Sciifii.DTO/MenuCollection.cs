using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO
{
    [Serializable]
    [XmlType("menus")]
    public class MenuCollection
    {
        [XmlAttribute("start")]
        public string StartMenuId { get; set; }

        [XmlElement("menu", typeof(Menu))]
        public List<Menu> Menus { get; set; }

        public Menu this[string menuId]
        {
            get
            {
                return Menus.FirstOrDefault(m => m.Id.Equals(menuId));
            }
        }
    }
}
