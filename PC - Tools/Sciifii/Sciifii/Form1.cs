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
        sciifii datas;
        bool blockList = false;
        bool job = false;
        string directory;

        public Form1()
        {
            InitializeComponent();
            checkedListBox1.DisplayMember = "text";

            using (Stream config = File.Open("config.xml", FileMode.Open, FileAccess.Read))
                datas = (sciifii)new XmlSerializer(typeof(sciifii)).Deserialize(config);

            List<sciifiiMode> modes = new List<sciifiiMode>();
            modes.Add(new sciifiiMode { text = "Advanced mode", options = "", flag = "" });
            modes.AddRange(datas.modes);

            sciifiiModeBindingSource.DataSource = modes;

            checkedListBox1.Items.Clear();
            foreach (sciifiiOption option in datas.options)
                if(!option.networkRequired)
					checkedListBox1.Items.Add(option, false);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (blockList)
                return;

            blockList = true;

            string[] options = comboBox1.SelectedValue.ToString().Split('|');

            checkedListBox1.Items.Clear();
            foreach (sciifiiOption option in datas.options)
                if(!option.networkRequired)
                    checkedListBox1.Items.Add(option, options.Contains(option.name));

            blockList = false;
        }

        private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (blockList)
                return;

            blockList = true;
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
            List<object> steps = new List<object>();

            foreach (sciifiiOption option in checkedListBox1.CheckedItems)
                options.Add(option.name);

            foreach (object o in datas.steps.Items)
            {
                string[] sopts = o.GetType().GetProperty("option").GetValue(o, null).ToString().Split('|');
                foreach (string sopt in sopts)
                    if (options.Contains(sopt))
                    {

                        steps.Add(o);
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
            Downloader d = new Downloader((object[])e.Argument, directory, datas, (BackgroundWorker)sender);
            d.ExecuteDownload();
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            progressBar1.Value = 0;

            if (e.Cancelled)
                Directory.Delete(directory + "\\sciifii", true);

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
