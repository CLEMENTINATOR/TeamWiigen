using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    public enum TI_Action
    {
        [XmlEnum("install")]
        Install,
        [XmlEnum("update")]
        Update,
        [XmlEnum("uninstall")]
        Uninstall,
        [XmlEnum("pack")]
        Pack,
        [XmlEnum("extract")]
        Extract,
        [XmlEnum("decrypt")]
        Decrypt
    }

    [Serializable]
    [XmlType("Title")]
    public class TitleInstaller : Step
    {
        [XmlAttribute(AttributeName = "action")]
        public TI_Action Action { get; set; }

        [XmlAttribute(AttributeName = "wad")]
        public String Wad { get; set; }

        [XmlAttribute(AttributeName = "id")]
        public String TitleId { get; set; }

        [XmlAttribute(AttributeName = "revision")]
        public UInt16 TitleRevision { get; set; }

        [XmlAttribute(AttributeName = "path")]
        public String Path { get; set; }

        public TitleInstaller(TI_Action action, string wad, string titleId, ushort titleRevision, string path)
        {
            this.Action = action;
            this.Wad = wad;
            this.TitleId = titleId;
            this.TitleRevision = titleRevision;
            this.Path = path;            
        } 
    }
}
