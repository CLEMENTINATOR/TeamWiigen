using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "menu")]
    public class Menu
    {
        [XmlAttribute(AttributeName = "id")]
        public String Id { get; set; }

        [XmlArray(ElementName = "modeMenuItem")]
        public List<ModeMenuItem> ModeMenuItem { get; set; }

        [XmlArray(ElementName = "separatorMenuItem")]
        public List<SeparatorMenuItem> SeparatorMenuItem { get; set; }

        [XmlArray(ElementName = "navigationMenuItem")]
        public List<NavigationMenuItem> NavigationMenuItem { get; set; }

        [XmlArray(ElementName = "switchMenuItem")]
        public List<SwitchMenuItem> SwitchMenuItem { get; set; }

        [XmlArray(ElementName = "startMenuItem")]
        public List<StartMenuItem> StartMenuItem { get; set; }

        [XmlArray(ElementName = "previousMenuItem")]
        public List<PreviousMenuItem> PreviousMenuItem { get; set; }

        [XmlArray(ElementName = "exitMenuItem")]
        public List<ExitMenuItem> ExitMenuItem { get; set; }
    }
}
