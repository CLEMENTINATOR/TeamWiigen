using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps.Patches
{
    [Serializable]
    [XmlType("SimplePatch")]
    public class SimplePatch : BasePatch
    {
        [XmlAttribute("value")]
        public string ValueString { get; set; }

        [XmlAttribute("pattern")]
        public string PatternString { get; set; }

        [XmlAttribute("module")]
        public string Module { get; set; }

        [XmlAttribute("offset")]
        public string Offset { get; set; }
        #region Helpers

        [XmlIgnore]
        public Byte[] Value
        {
            get
            {
                List<Byte> bytes = new List<byte>();
                foreach (String byteString in ValueString.Split(','))
                {
                    bytes.Add(byte.Parse(byteString.Trim().Remove(0, 2), System.Globalization.NumberStyles.HexNumber));
                }

                return bytes.ToArray();
            }
        }

        [XmlIgnore]
        public Byte[] Pattern
        {
            get
            {
                List<Byte> bytes = new List<byte>();
                foreach (String byteString in PatternString.Split(','))
                {
                    bytes.Add(byte.Parse(byteString.Trim().Remove(0,2), System.Globalization.NumberStyles.HexNumber));
                }

                return bytes.ToArray();
            }
        }

        #endregion
    }
}
