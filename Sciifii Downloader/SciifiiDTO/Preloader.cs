using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType("Preloader")]
    public class Preloader : Step
    {
        [XmlAttribute(AttributeName = "file")]
        public String File { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public Preloader()
        { }
        
        public Preloader(string file)
        {
            this.File = file;
        }
    }
}
