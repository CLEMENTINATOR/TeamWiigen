using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using SciifiiDTO.Corp;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType("CorpInstaller")]
    public class CiosCorp : Step
    {
        [XmlArrayItem(ElementName = "module", Type = typeof(CorpModule))]
        [XmlArray(ElementName = "modules")]
        public List<CorpModule> Modules { get; set; }

        [XmlArray(ElementName = "items")]
        public List<CorpItem> Items { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public CiosCorp()
        {
            this.Modules = new List<CorpModule>();
            this.Items = new List<CorpItem>();
        }
        
        public CiosCorp(List<CorpModule> modules, List<CorpItem> items)
        {
            this.Modules = modules;
            this.Items = items;
        }
    }
}
