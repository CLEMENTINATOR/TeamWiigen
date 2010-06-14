using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.ComponentModel;

namespace SciifiiDTO
{
    [Serializable]
    public abstract class Step
    {
        [XmlAttribute(AttributeName = "option")]
        public String OptionsString { get; set; }

        [XmlIgnore]
        public List<String> Options { get { return OptionsString.Split('|').ToList(); } }
    }
}
