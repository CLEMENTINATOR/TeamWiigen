using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.IO;
using SciifiiDTO;
using System.Xml.Serialization;

namespace Sciifii
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            String fileName = "config.xml";
            
            //Load config.xml
            if (!File.Exists(fileName))
            {
                OpenFileDialog openFileDialog1 = new OpenFileDialog();
                MessageBox.Show("File config.xml not found", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    fileName = openFileDialog1.FileName;
                else
                {
                    MessageBox.Show("config.xml is expected, application will close now", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }

            try
            {
                SciifiiConfiguration datas = null;
                using (Stream config = File.Open(fileName, FileMode.Open, FileAccess.Read))
                    datas = (SciifiiConfiguration)new XmlSerializer(typeof(SciifiiConfiguration)).Deserialize(config);

                switch (datas.Version)
                {
                    case 5:
                        Application.Run(new MainFormV5(datas)); break;
                    default:
                        Application.Run(new MainFormV4(datas)); break;
                }
            }
            catch
            { /*Nothing to do just leave if filename empty*/ }
        }
    }
}
