using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "navigationMenuItem")]
    public class NavigationMenuItem
    {
        [XmlAttribute(AttributeName = "text")]
        public String Text { get; set; }

        [XmlAttribute(AttributeName = "menuId")]
        public String MenuId { get; set; }

        [XmlAttribute(AttributeName = "saveOptions")]
        public Boolean SaveOptions { get; set; }
    }
}
