using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using SciifiiDTO;
using System.Xml.Serialization;
using SciifiiBusiness;
using System.Diagnostics;

namespace Sciifii
{
    public partial class MainForm : Form
    {
        #region private
        private SciifiiConfiguration datas;
        private bool blockList = false;
        private bool job = false;
        private string directory;
        private List<String> hiddenOptions;
        private TaskFactory m_taskFact;

        private Stopwatch m_total = new Stopwatch();
        private Stopwatch m_step = new Stopwatch();

        private void StopJob()
        {
            m_UpTextBox(tbStatus, "Cancel in progress");
            backgroundWorker1.CancelAsync();
        }

        private void StartJob()
        {
            m_UpTextBox(tbStatus, "--------------------------------------------");
            m_UpTextBox(tbStatus, "Start of process, it could take some time...");
            m_total.Start();
            m_step.Start();
            List<string> options = new List<string>();
            List<Step> steps = new List<Step>();

            foreach (Option option in clbOption.CheckedItems)
                options.Add(option.Name);

            options.AddRange(hiddenOptions);

            foreach (Step s in datas.Steps)
            {
                foreach (string sopt in s.Options)
                    if (options.Contains(sopt))
                    {
                        steps.Add(s);
                        break;
                    }
            }

            backgroundWorker1.RunWorkerAsync(steps.ToArray());
        }

        private void Display_Message(string message)
        {
            m_step.Stop();
            ModifTextBox(tbStatus, message + " downloaded in " + m_step.ElapsedMilliseconds + " ms");
            m_step.Reset();
            m_step.Start();
        }

        private void UploadToSd()
        {
            if (MessageBox.Show("The treatment is finished, move files to SD card?",
                                "Success",
                                MessageBoxButtons.YesNo,
                                MessageBoxIcon.Question) == DialogResult.Yes)
                if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
                {
                    String sdRoot = folderBrowserDialog1.SelectedPath;//Path.GetPathRoot(folderBrowserDialog1.SelectedPath);
                    if(!sdRoot.EndsWith("\\"))
                        sdRoot += "\\";
                    try
                    {
                        foreach (FileInfo toMove in new DirectoryInfo(directory).GetFiles("*", SearchOption.AllDirectories))
                        {
                            string dir = sdRoot + toMove.DirectoryName.Replace(directory, "");
                            if (!Directory.Exists(dir))
                                Directory.CreateDirectory(dir);
                            toMove.CopyTo(Path.Combine(dir, toMove.Name));
                        }
                        
                        MessageBox.Show("Files moved with success",
                                        "Success",
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Error on moving files to SD card directory\r\n" + ex.Message,
                                "Error",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
                    }
                }
        }
        #endregion

        #region public
        public MainForm()
        {
            InitializeComponent();

            m_taskFact = new TaskFactory();
            //Register downloader message event
            if (m_taskFact.message == null)
                m_taskFact.message += new MessageEventHandler(Display_Message);
            
            //Register delegate to update textbox with thread
            m_UpTextBox = new UpdateTextBoxDelegate(this.UpdateTextBox);

            tbStatus.Text = "";
            hiddenOptions = new List<string>();

            clbOption.DisplayMember = "text";

            String fileName = "config.xml";
            //Load config.xml
            if (!File.Exists(fileName))
            {
                MessageBox.Show("File config.xml not found", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    fileName = openFileDialog1.FileName;
                else
                {
                    MessageBox.Show("config.xml is expected, application will close now", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    this.Close();
                }
            }

            using (Stream config = File.Open(fileName, FileMode.Open, FileAccess.Read))
                datas = (SciifiiConfiguration)new XmlSerializer(typeof(SciifiiConfiguration)).Deserialize(config);
                                     
            UpdateTextBox(tbStatus, "Config.xml load with success.");

            List<Mode> modes = new List<Mode>();
            modes.Add(new Mode { Text = "Advanced mode", OptionsString = "", Flag = "" });
            modes.AddRange(datas.Modes);

            sciifiiModeBindingSource.DataSource = modes;

            clbOption.Items.Clear();
            foreach (Option option in datas.Options)
                if (!option.Hidden)
                    clbOption.Items.Add(option, false);

            ddlRegion.DataSource = Enum.GetNames(typeof(Regions)).Where(x => x != "ALL").OrderBy(x => x).ToList();        
        }
        #endregion

        #region events
        protected void lbMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (blockList)
                return;

            blockList = true;

            hiddenOptions.Clear();
            List<string> options = lbMode.SelectedValue as List<string>;

            clbOption.Items.Clear();
            if (options != null)
                foreach (Option option in datas.Options)
                    if (option.Hidden)
                    {
                        if (options.Contains(option.Name))
                            hiddenOptions.Add(option.Name);
                    }
                    else
                        clbOption.Items.Add(option, options.Contains(option.Name));

            blockList = false;
        }

        protected void clbOption_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (blockList)
                return;

            blockList = true;
            hiddenOptions.Clear();
            lbMode.SelectedIndex = 0;
            blockList = false;
        }

        protected void btnDownload_Click(object sender, EventArgs e)
        {
            if (!job)
            {
                FolderBrowserDialog dial = new FolderBrowserDialog();
                if (dial.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    datas.SelectedRegion = (Regions)Enum.Parse(typeof(Regions), ddlRegion.SelectedValue.ToString());
                    directory = dial.SelectedPath;
                    StartJob();
                }
            }
            else
                StopJob();
        }

        protected void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            this.Invoke(new MethodInvoker(delegate()
            {
                btnDownload.Text = "Cancel";
            }));
            job = true;
            
            Directory.CreateDirectory(directory);
            CompositeInstaller container = new CompositeInstaller();

            foreach (Step s in (IEnumerable<Step>)e.Argument)
                container.Steps.Add(s);

            m_taskFact.CreateTask(container).Prepare(directory, datas, (BackgroundWorker)sender, e, 0, container.StepsFullCount);
        }

        protected void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            pbStatus.Value = e.ProgressPercentage;
        }

        protected void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            m_total.Stop();
            UpdateTextBox(tbStatus, "--------------------------------------------");
            UpdateTextBox(tbStatus, "Download finish, total time: " + (m_total.ElapsedMilliseconds / 1000) + " s");
            UpdateTextBox(tbStatus, "--------------------------------------------");

            pbStatus.Value = 0;
            
            if (e.Error != null)
                UpdateTextBox(tbStatus, "An error occured;\n" + e.Error.Message);

            this.Invoke(new MethodInvoker(delegate()
            {
                btnDownload.Text = "Download";
            }));
            job = false;

            if (e.Error == null)
                UploadToSd();
        }
        #endregion

        #region ControlManagment
        private delegate void UpdateTextBoxDelegate(System.Windows.Forms.TextBox tb, String value);
        private UpdateTextBoxDelegate m_UpTextBox;

        private void UpdateTextBox(System.Windows.Forms.TextBox tb, String value)
        {
            value = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss") + " : " + value;
            // Small function for writing text to the statusbox...
            if (tb.Text == "")
                tb.Text = value;
            else
                tb.Text += "\r\n" + value;

            // Scroll to end of text box.
            tb.SelectionStart = tb.TextLength;
            tb.ScrollToCaret();
        }

        private void ModifTextBox(System.Windows.Forms.TextBox tb, String value)
        {
            object[] arg = { tb, value };
            tb.Invoke(m_UpTextBox, arg);
        }
        #endregion
    }
}
