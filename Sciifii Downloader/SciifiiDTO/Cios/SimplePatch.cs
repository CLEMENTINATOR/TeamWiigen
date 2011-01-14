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
        [XmlAttribute(AttributeName = "module")]
        public String Module { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public SimplePatch()
        { }
        
        public SimplePatch(string module)
        {
            this.Module = module;
        }
    }
}
