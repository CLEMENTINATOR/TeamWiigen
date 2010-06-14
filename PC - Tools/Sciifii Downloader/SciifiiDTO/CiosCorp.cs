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
    }
}
