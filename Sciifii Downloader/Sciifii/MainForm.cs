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

        private void StopJob()
        {
            m_UpTextBox(tbStatus, "Cancel in progress");
            backgroundWorker1.CancelAsync();
        }

        private void StartJob()
        {
            m_UpTextBox(tbStatus, "Download started");
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
        #endregion

        #region public
        public MainForm()
        {
            InitializeComponent();

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

            m_UpTextBox(tbStatus, "Config.xml succesfully loaded.");

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
            Downloader d = new Downloader(e, directory, datas, (BackgroundWorker)sender);
            d.ExecuteDownload();
        }

        protected void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            pbStatus.Value = e.ProgressPercentage;
            m_UpTextBox(tbStatus, "");
        }

        protected void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            m_UpTextBox(tbStatus, "Download finish");
            pbStatus.Value = 0;
            
            if (e.Error != null)
               m_UpTextBox(tbStatus, "An error occured;\n" + e.Error.Message);

            this.Invoke(new MethodInvoker(delegate()
            {
                btnDownload.Text = "Download";
            }));
            job = false;
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
