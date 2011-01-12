using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Log
{
    public enum LogCategory
    {
        [XmlEnum(Name = "error")]
        ERROR,
        [XmlEnum(Name = "warning")]
        WARNING,
        [XmlEnum(Name = "info")]
        INFO,
        [XmlEnum(Name = "all")]
        ALL,
    }
}
