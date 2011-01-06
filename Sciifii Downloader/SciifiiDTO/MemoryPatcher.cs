﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using SciifiiDTO.Cios;

namespace SciifiiDTO
{
    [Serializable]
    [XmlType("MemoryPatcher")]
    public class MemoryPatcher : Step
    {
        [XmlArrayItem(ElementName = "patch", Type = typeof(SimplePatch))]
        public List<SimplePatch> Patches { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public MemoryPatcher()
        {
            this.Patches = new List<SimplePatch>();
        }
        
        public MemoryPatcher(List<SimplePatch> patches)
        {
            this.Patches = patches;
        }
    }
}
