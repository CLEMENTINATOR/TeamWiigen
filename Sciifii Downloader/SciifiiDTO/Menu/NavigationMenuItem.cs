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

        /// <summary>
        /// Need by serialization
        /// </summary>
        public NavigationMenuItem()
        { }
        
        public NavigationMenuItem(string text, string menuId, bool saveOptions)
        {
            this.Text = text;
            this.MenuId = menuId;
            this.SaveOptions = saveOptions;
        }
    }
}
