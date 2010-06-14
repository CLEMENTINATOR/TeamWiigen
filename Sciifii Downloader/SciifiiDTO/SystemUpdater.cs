using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using SciifiiDTO.Updater;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType("SystemUpdater")]
    public class SystemUpdater : Step
    {
        public SystemUpdater()
        {
            Titles = new List<Title>();
        }

        [XmlElement(ElementName = "title", Type = typeof(Title))]
        public List<Title> Titles { get; set; }
    }
}
