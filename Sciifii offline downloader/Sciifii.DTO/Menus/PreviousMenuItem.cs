using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    [XmlType("previousMenuItem")]
    public class PreviousMenuItem : NavigationMenuItem
    {
        public PreviousMenuItem()
        {
            this.SaveOptions = false;
            this.MenuId = "..";
        }
    }
}
