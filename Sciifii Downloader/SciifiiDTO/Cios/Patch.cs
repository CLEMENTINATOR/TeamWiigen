using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    public abstract class Patch
    {
        [XmlAttribute(AttributeName = "pattern")]
        public String Pattern { get; set; }

        [XmlAttribute(AttributeName = "value")]
        public String Value { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Patch()
        { }

        public Patch(string pattern, string value)
        {
            this.Pattern = pattern;
            this.Value = value;
        }
    }
}
