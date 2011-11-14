using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    public enum TitleAction
    {
        [XmlEnum("install")]
        Install,
        [XmlEnum("uninstall")]
        Uninstall,
        [XmlEnum("pack")]
        PackAsWad,
        [XmlEnum("extract")]
        Extract,
        [XmlEnum("decrypt")]
        Decrypt,
        [XmlEnum("update")]
        Update,
    }

    [Serializable]
    [XmlType("Title")]
    public class Title : BaseStep
    {
        [XmlAttribute("id")]
        public string Id { get; set; }

        [XmlAttribute("revision")]
        public ushort Revision { get; set; }

        [XmlAttribute("wad")]
        public string WadFile { get; set; }

        [XmlAttribute("path")]
        public string Path { get; set; }

        [XmlAttribute("fakesign")]
        public bool FakeSign { get; set; }

        [XmlAttribute("action")]
        public TitleAction Action { get; set; }

        public Title()
        {
            Id = "0";
            Revision = 0;
        }
    }
}
