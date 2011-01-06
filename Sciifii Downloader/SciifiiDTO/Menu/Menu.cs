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

        [XmlElementAttribute(ElementName = "modeMenuItem")]
        public List<ModeMenuItem> ModeMenuItem { get; set; }

        [XmlElementAttribute(ElementName = "separatorMenuItem")]
        public List<SeparatorMenuItem> SeparatorMenuItem { get; set; }

        [XmlElementAttribute(ElementName = "navigationMenuItem")]
        public List<NavigationMenuItem> NavigationMenuItem { get; set; }

        [XmlElementAttribute(ElementName = "switchMenuItem")]
        public List<SwitchMenuItem> SwitchMenuItem { get; set; }

        [XmlElementAttribute(ElementName = "startMenuItem")]
        public List<StartMenuItem> StartMenuItem { get; set; }

        [XmlElementAttribute(ElementName = "previousMenuItem")]
        public List<PreviousMenuItem> PreviousMenuItem { get; set; }

        [XmlElementAttribute(ElementName = "exitMenuItem")]
        public List<ExitMenuItem> ExitMenuItem { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Menu()
        { 
            this.ModeMenuItem  = new List<ModeMenuItem>();
            this.SeparatorMenuItem = new List<SeparatorMenuItem>();
            this.NavigationMenuItem = new List<NavigationMenuItem>();
            this.SwitchMenuItem = new List<SwitchMenuItem>();
            this.StartMenuItem = new List<StartMenuItem>();
            this.PreviousMenuItem = new List<PreviousMenuItem>();
            this.ExitMenuItem = new List<ExitMenuItem>();
        }
        
        public Menu(string id, 
            List<ModeMenuItem> modeMenuItem, 
            List<SeparatorMenuItem> separatorMenuItem, 
            List<NavigationMenuItem> navigationMenuItem,
            List<SwitchMenuItem> switchMenuItem,
            List<StartMenuItem> startMenuItem,
            List<PreviousMenuItem> previousMenuItem,
            List<ExitMenuItem> exitMenuItem)
        {
            this.Id = id;
            this.ModeMenuItem = modeMenuItem;
            this.SeparatorMenuItem = separatorMenuItem;
            this.NavigationMenuItem = navigationMenuItem;
            this.SwitchMenuItem = switchMenuItem;
            this.StartMenuItem = startMenuItem;
            this.PreviousMenuItem = previousMenuItem;
            this.ExitMenuItem = exitMenuItem;
        }
    }
}
