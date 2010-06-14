using System;
using System.Xml.Serialization;

namespace SciifiiDTO
{
	public enum Regions
	{
        [XmlEnum(Name = "-1")]
        ALL = -1,
        [XmlEnum(Name = "0")]
		JAP = 0,
        [XmlEnum(Name = "1")]
		USA = 1,
        [XmlEnum(Name = "2")]
		EUR = 2,
        [XmlEnum(Name = "4")]
		KOR = 4,
	}
}