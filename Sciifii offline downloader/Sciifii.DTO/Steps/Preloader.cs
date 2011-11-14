using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace Sciifii.DTO.Steps
{
    [Serializable]
    [XmlType("Preloader")]
    public class Preloader : FileDownloader
    {
    }
}
