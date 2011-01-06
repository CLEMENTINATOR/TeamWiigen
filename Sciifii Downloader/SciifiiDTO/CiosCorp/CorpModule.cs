using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Corp
{
    [Serializable]
    [XmlType("corpModule")]
    public class CorpModule
    {
        [XmlAttribute(AttributeName = "type")]
        public String ModuleName { get; set; }

        [XmlAttribute(AttributeName = "name")]
        public String Name { get; set; }

        [XmlAttribute(AttributeName = "file")]
        public String File { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public CorpModule()
        { }
        
        public CorpModule(string moduleName, string name, string file)
        {
            this.ModuleName = moduleName;
            this.Name = name;
            this.File = file;
        }
    }
}
