using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("SimplePatch")]
    public class SimplePatch : Patch
    {
        [XmlAttribute(AttributeName = "pattern")]
        public String Pattern { get; set; }

        [XmlAttribute(AttributeName = "value")]
        public String Value { get; set; }

        [XmlAttribute(AttributeName = "module")]
        public String Module { get; set; }

        public SimplePatch(string pattern, string value, string module)
        {
            this.Pattern = pattern;
            this.Value = value;
            this.Module = module;
        }
    }
}
