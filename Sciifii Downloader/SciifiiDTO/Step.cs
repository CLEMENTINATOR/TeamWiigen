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
                List<string> opts = OptionsString.Split(',').ToList();
                return (from o in opts select (Regions)Enum.Parse(typeof(Regions), o)).ToList();
            }
        }

        public Step()
        {
            RegionsString = "-1";
        }
    }
}
