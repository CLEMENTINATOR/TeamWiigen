using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    public enum SystemTaskAction
    {
        [XmlEnum("exit")]
        Exit,
        [XmlEnum("reboot")]
        Reboot
    }

    [Serializable]
    [XmlType("System")]
    public class SystemTask : BaseStep
    {
        [XmlAttribute("action")]
        public SystemTaskAction Action { get; set; }

        [XmlAttribute("message")]
        public string Message { get; set; }
    }
}
