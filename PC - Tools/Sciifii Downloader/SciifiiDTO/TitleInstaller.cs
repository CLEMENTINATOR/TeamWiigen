﻿using System;
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
        public TitleInstaller()
        {
            Action = TI_Action.Install;
            TitleId = "";
            TitleRevision = 0;
        }

        [XmlAttribute(AttributeName = "action")]
        public TI_Action Action { get; set; }

        [XmlAttribute(AttributeName = "wad")]
        public string Wad { get; set; }

        [XmlAttribute(AttributeName = "id")]
        public String TitleId { get; set; }

        [XmlAttribute(AttributeName = "revision")]
        public UInt16 TitleRevision { get; set; }

        [XmlAttribute(AttributeName = "path")]
        public string Path { get; set; }
    }
}
