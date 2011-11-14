using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Menus
{
    [Serializable]
    public abstract class MenuItem
    {
        [XmlIgnore]
        public virtual bool BreakBefore
        {
            get { return false; }
        }

        [XmlIgnore]
        public virtual bool BreakAfter
        {
            get { return false; }
        }
    }
}
