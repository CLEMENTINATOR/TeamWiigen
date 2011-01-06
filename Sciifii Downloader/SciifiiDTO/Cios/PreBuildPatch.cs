﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Cios
{
    [Serializable]
    [XmlType("prebuild")]
    public class PreBuildPatch : Patch
    {
        [XmlAttribute(AttributeName = "name")]
        public String Name { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public PreBuildPatch()
        { }
        
        public PreBuildPatch(string name)
        {
            this.Name = name;
        }
    }
}
