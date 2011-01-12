using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Log
{
    public enum LogType
    {
        [XmlEnum(Name = "gecko")]
        GECKO,
        [XmlEnum(Name = "file")]
        FILE,
        [XmlEnum(Name = "web")]
        WEB,
    }
}
