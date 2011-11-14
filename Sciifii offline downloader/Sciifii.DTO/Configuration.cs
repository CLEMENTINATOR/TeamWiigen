using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using Sciifii.DTO.Steps;

namespace Sciifii.DTO
{
    [Serializable]
    [XmlRoot("sciifii")]
    public class Configuration
    {
        [XmlArray("logs")]
        [XmlArrayItem("log", typeof(Log))]
        public List<Log> Logs { get; set; }

        [XmlArray("files")]
        [XmlArrayItem("file", typeof(Sciifii.DTO.File))]
        public List<Sciifii.DTO.File> Files { get; set; }

        private string disclaimer;
        [XmlElement("Disclaimer")]
        public string Disclaimer
        {
            get { return disclaimer; }
            set { disclaimer = value.Replace("\\n", ""); }
        }

        [XmlElement("menus")]
        public MenuCollection MenuCollection { get; set; }

        [XmlArray("steps")]
        [XmlArrayItem("MemoryPatcher", typeof(MemoryPatcher))]
        [XmlArrayItem("CiosInstaller", typeof(CiosInstaller))]
        [XmlArrayItem("CompositeInstaller", typeof(CompositeInstaller))]
        [XmlArrayItem("Title", typeof(Title))]
        [XmlArrayItem("FileSystem", typeof(FileSystem))]
        [XmlArrayItem("Preloader", typeof(Preloader))]
        [XmlArrayItem("FileDownloader", typeof(FileDownloader))]
        public List<BaseStep> Steps { get; set; }

        [XmlAttribute("workingDirectory")]
        public string WorkingDirectory { get; set; }

        [XmlIgnore]
        public List<Switch> Switches { get; set; }

        [XmlIgnore]
        public List<Switch> TempSwitches { get; set; }

        [XmlIgnore]
        public List<BaseStep> ActiveSteps
        {
            get
            {
                return Steps.FindAll(s => Switches.FirstOrDefault(sw => sw.Active && sw.Key == s.Key) != null);
            }
        }

        public Configuration()
        {
            WorkingDirectory = "sd:/sciifii/temp";
            Switches = new List<Switch>();
            TempSwitches = new List<Switch>();
            Logs = new List<Log>();
            Files = new List<Sciifii.DTO.File>();
            MenuCollection = new MenuCollection();
            Steps = new List<BaseStep>();
        }

        public static Configuration Current { get; set; }

        public static Configuration LoadConfiguration(string configPath = "config.xml")
        {
            Current = null;
            using (FileStream fs = System.IO.File.OpenRead(configPath))
            {
                XmlSerializer serializer = new XmlSerializer(typeof(Configuration), "");
                Current = serializer.Deserialize(fs) as Configuration;
            }

            return Current;
        }

        public void ModifySwitchStatus(string switchKey)
        {
            Switch selectedSwitch = Switches.FirstOrDefault(s => s.Key == switchKey);
            if (selectedSwitch != null)
                TempSwitches.Add(new Switch { Active = !selectedSwitch.Active, Key = selectedSwitch.Key });
            else
                TempSwitches.Add(new Switch { Key = switchKey, Active = true });
        }

        public void ValidateSwitchSelection(bool validate)
        {
            if (validate)
            {
                foreach (Switch s in TempSwitches)
                {
                    Switch real = Switches.FirstOrDefault(sw => sw.Key == s.Key);
                    if (real != null)
                        real.Active = s.Active;
                    else
                        Switches.Add(s);
                }
            }
            TempSwitches.Clear();
        }

        public void SetMode(List<String> switches)
        {
            foreach (string key in switches)
            {
                Switch selectedSwitch = Switches.FirstOrDefault(s => s.Key == key);
                if (selectedSwitch != null)
                    selectedSwitch.Active = true;
                else
                    Switches.Add(new Switch { Key = key, Active = true });
            }

            foreach (Switch s in Switches)
            {
                if (!switches.Contains(s.Key))
                    s.Active = false;
            }
        }

        [XmlIgnore]
        public StepRegion SelectedRegion { get; set; }
    }
}
