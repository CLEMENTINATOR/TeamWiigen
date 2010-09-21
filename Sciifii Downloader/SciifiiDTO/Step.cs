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

        [XmlAttribute(AttributeName = "regions")]
        public String RegionsString { get; set; }

        [XmlIgnore]
        public List<String> Options { get { return OptionsString.Split('|').ToList(); } }

        [XmlIgnore]
        public List<Regions> Regions
        {
            get
            {
                List<string> regs = RegionsString.Split(',').ToList();
                return (from r in regs select (Regions)int.Parse(r.Trim())).ToList();
            }
        }

        public Step()
        {
            RegionsString = "-1";
        }
    }
}
