using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType("Preloader")]
    public class Preloader : Step
    {
        [XmlAttribute(AttributeName = "file")]
        public string File { get; set; }
    }
}
