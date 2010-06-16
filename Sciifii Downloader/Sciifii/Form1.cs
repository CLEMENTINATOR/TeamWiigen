using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;
using System.IO;
using SciifiiDTO;

namespace Sciifii
{
    public partial class Form1 : Form
    {
        SciifiiConfiguration datas;
        bool blockList = false;
        bool job = false;
        string directory;

        List<String> hiddenOptions;

        public Form1()
        {
            InitializeComponent();
            hiddenOptions = new List<string>();

            checkedListBox1.DisplayMember = "text";

            using (Stream config = File.Open("config.xml", FileMode.Open, FileAccess.Read))
                datas = (SciifiiConfiguration)new XmlSerializer(typeof(SciifiiConfiguration)).Deserialize(config);

            List<Mode> modes = new List<Mode>();
            modes.Add(new Mode { Text = "Advanced mode", OptionsString = "", Flag = "" });
            modes.AddRange(datas.Modes);

            sciifiiModeBindingSource.DataSource = modes;

            checkedListBox1.Items.Clear();
            foreach (Option option in datas.Options)
                if (!option.Hidden)
                    checkedListBox1.Items.Add(option, false);

            ddlRegion.DataSource = Enum.GetNames(typeof(Regions)).Where(x => x != "ALL").OrderBy(x => x).ToList();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (blockList)
                return;

            blockList = true;

            hiddenOptions.Clear();
            List<string> options = comboBox1.SelectedValue as List<string>;

            checkedListBox1.Items.Clear();
            if (options != null)
                foreach (Option option in datas.Options)
                    if (option.Hidden)
                    {
                      if(options.Contains(option.Name))
                        hiddenOptions.Add(option.Name);
                    }
                    else
                        checkedListBox1.Items.Add(option, options.Contains(option.Name));

            blockList = false;
        }

        private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (blockList)
                return;

            blockList = true;
            hiddenOptions.Clear();
            comboBox1.SelectedIndex = 0;
            blockList = false;
        }

        private void button1_Click(object sender, EventArgs e)
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

        private void StopJob()
        {
            backgroundWorker1.CancelAsync();
        }

        private void StartJob()
        {
            List<string> options = new List<string>();
            List<Step> steps = new List<Step>();

            foreach (Option option in checkedListBox1.CheckedItems)
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

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            this.Invoke(new MethodInvoker(delegate()
                 {
                     button1.Text = "Cancel";
                 }));
            job = true;
            Downloader d = new Downloader(e, directory, datas, (BackgroundWorker)sender);
            d.ExecuteDownload();
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            progressBar1.Value = 0;

            if (e.Error != null)
                MessageBox.Show(this, "An error occured;\n" + e.Error.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

            this.Invoke(new MethodInvoker(delegate()
            {
                button1.Text = "Download";
            }));
            job = false;
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar1.Value = e.ProgressPercentage;
        }

    }
}
