using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    public enum StepRegion
    {
        Japan = 0,
        USA = 1,
        Europe = 2,
        Korean = 4,
    }

    [Serializable]
    public class BaseStep
    {
        [XmlAttribute("option")]
        public string Key { get; set; }

        [XmlAttribute("regions")]
        public string RegionsString { get; set; }

        [XmlIgnore]
        public List<StepRegion> Regions 
        {
            get
            {
                List<StepRegion> l = new List<StepRegion>();
                if (String.IsNullOrWhiteSpace(RegionsString))
                    return l;

                foreach (string regionId in RegionsString.Split(','))
                    l.Add((StepRegion)int.Parse(regionId));
                return l;
            }
        }
    }
}
