﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType(TypeName = "WadBatchInstaller")]
    public class WadBatchInstaller : Step
    {
        [XmlAttribute(AttributeName = "folder")]
        public String Folder { get; set; }
    }
}