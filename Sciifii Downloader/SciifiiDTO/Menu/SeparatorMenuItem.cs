﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SciifiiDTO.Menu
{
    [Serializable]
    [XmlType(TypeName = "separatorMenuItem")]
    public class SeparatorMenuItem
    {
        [XmlAttribute(AttributeName = "char")]
        public String Char { get; set; }

        /// <summary>
        /// Need by serialization
        /// </summary>
        public SeparatorMenuItem()
        { }
        
        public SeparatorMenuItem(string car)
        {
            this.Char = car;
        }
    }
}
