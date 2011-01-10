using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SciifiiDTO;
using SciifiiBusiness;
using System.Diagnostics;
using System.IO;
using SciifiiDTO.Menu;
using Sciifii.Properties;
using System.Resources;
using Sciifii.Utils;

namespace Sciifii
{
    public partial class MainFormV5 : Form
    {
        #region private
        private SciifiiConfiguration datas;
        private String fileName;
        private bool job = false;
        private bool canceledJob = false;
        private string directory;
        private List<String> hiddenOptions;
        private TaskFactory m_taskFact;

        private Stopwatch m_total = new Stopwatch();
        private Stopwatch m_step = new Stopwatch();

        LogForm m_log = new LogForm();

        ResourceManager resource = new ResourceManager(typeof(MainFormV5));

        /// <summary>
        /// Add return button to panel
        /// </summary>
        /// <param name="pnl">Panel to add return button</param>
        private void AddReturnButton(Panel pnl)
        {
            Button btn = new Button();
            btn.Name = Convert.ToString(resource.GetString("$Exit"));
            btn.Image = Resources.exitbutton_normal;
            btn.Width = Resources.exitbutton_normal.Width;
            btn.Height = Resources.exitbutton_normal.Height;
            btn.Click += new EventHandler(btn_ExitClick);
            
            btn.Top = 184;
            btn.Left = 3;
            pnl.Controls.Add(btn);
        }

        /// <summary>
        /// Add download button to panel
        /// </summary>
        /// <param name="pnl">Panel to add download button</param>
        private void AddDownloadButton(Panel pnl)
        {
            Button btn = new Button();
            btn.Text = Convert.ToString(resource.GetString("$Download"));
            btn.Name = "¤advanced¤";
            btn.Click += new EventHandler(btnDownload_Click);

            btn.Top = 204;
            btn.Left = 470;
            pnl.Controls.Add(btn);
        }

        /// <summary>
        /// Add tooltip to form control
        /// </summary>
        /// <param name="ctrl">Control to add tooltip</param>
        /// <param name="display">String to display in tooltip</param>
        private void AddToolTip(Control ctrl, String display)
        {
            ToolTip tt = new ToolTip();
            tt.AutoPopDelay = 5000;
            tt.InitialDelay = 1000;
            tt.ReshowDelay = 500;
            tt.ShowAlways = true;

            tt.SetToolTip(ctrl, display);
        }
        
        /// <summary>
        /// This method display items in panel with CheckBox dynamicly
        /// </summary>
        /// <param name="items">List string represent item</param>
        /// <param name="nbColumn">Number of column in panel</param>
        private void DisplayAdvancedMenu(List<SwitchMenuItem> items, int nbColumn)
        {
            pnlMenus.Visible = pnlModeMenu.Visible = false;
            pnlModeMenu.Controls.Clear();

            CheckBox cb = new CheckBox();

            int nbElem = items.Count;

            if (nbElem < nbColumn)
                nbColumn = nbElem;

            int nbLine = nbElem / nbColumn;
            if ((((Decimal)nbElem / nbColumn) - nbLine) * 100 != 0)
                nbLine++;

            int[] topStep = new int[Convert.ToInt32(nbLine)];
            int[] leftStep = new int[nbColumn];

            for (int i = 1; i < topStep.Length + 1; i++)
            {
                topStep[i - 1] = i * pnlModeMenu.Height / (nbLine + 1) - cb.Height / 2;
            }

            for (int i = 1; i < leftStep.Length + 1; i++)
            {
                leftStep[i - 1] = i * pnlModeMenu.Width / (nbColumn + 1);
            }

            int currentLine = 0;
            for (int i = 0; i < nbElem; i++)
            {
                cb = new CheckBox();
                cb.Name = cb.Text = items[i].Name.Trim();
                cb.Enabled = !items[i].Hidden;
                
                cb.Top = topStep[currentLine];
                cb.Left = leftStep[i - (currentLine * nbColumn)] - cb.Width / 2;

                AddToolTip(cb, items[i].Text.Trim());
                pnlModeMenu.Controls.Add(cb);

                if ((i + 1) % nbColumn == 0)
                    currentLine++;
            }

            AddReturnButton(pnlModeMenu);
            AddDownloadButton(pnlModeMenu);

            pnlModeMenu.Visible = true;
        }
        
        /// <summary>
        /// This method display items in panel with Button dynamicly
        /// </summary>
        /// <param name="pnl">Panel where display button</param>
        /// <param name="items">List string represent item</param>
        /// <param name="nbColumn">Number of column in panel</param>
        private void DisplaySecondMenu(List<ModeMenuItem> items, int nbColumn)
        {
            pnlMenus.Visible = false;
            pnlModeMenu.Controls.Clear();

            Button btn = new Button();

            int nbElem = items.Count;

            if (nbElem < nbColumn)
                nbColumn = nbElem;

            int nbLine = nbElem / nbColumn;
            if ((((Decimal)nbElem / nbColumn) - nbLine) * 100 != 0)
                nbLine++;

            int[] topStep = new int[Convert.ToInt32(nbLine)];
            int[] leftStep = new int[nbColumn];

            for (int i = 1; i < topStep.Length + 1; i++)
            {
                topStep[i - 1] = i * pnlModeMenu.Height / (nbLine + 1) - btn.Height / 2;
            }

            for (int i = 1; i < leftStep.Length + 1; i++)
            {
                leftStep[i - 1] = i * pnlModeMenu.Width / (nbColumn + 1);
            }

            int currentLine = 0;
            for (int i = 0; i < nbElem; i++)
            {
                btn = new Button();
                btn.Name = items[i].Switches;
                btn.Click += new EventHandler(btnDownload_Click);

                btn.Text = items[i].Text.Trim();
                if (btn.Text.Length * 7 > btn.Width)
                    btn.Width = btn.Text.Length * 7;

                btn.Top = topStep[currentLine];
                btn.Left = leftStep[i - (currentLine * nbColumn)] - btn.Width / 2;

                pnlModeMenu.Controls.Add(btn);

                if ((i + 1) % nbColumn == 0)
                    currentLine++;
            }

            AddReturnButton(pnlModeMenu);

            pnlModeMenu.Visible = true;
        }
        
        /// <summary>
        /// This method display items in panel with Button dynamicly
        /// </summary>
        /// <param name="pnl">Panel where display button</param>
        /// <param name="items">List string represent item</param>
        /// <param name="nbColumn">Number of column in panel</param>
        private void DisplayMainMenu(List<SciifiiDTO.Menu.Menu> items, int nbColumn)
        {
            pnlModeMenu.Visible = false;
            pnlMenus.Controls.Clear();
            
            Button btn = new Button();

            int nbElem = items.Count;
            
            if (nbElem < nbColumn)
                nbColumn = nbElem;

            int nbLine = nbElem / nbColumn;
            if ((((Decimal)nbElem / nbColumn) - nbLine) * 100 != 0)
                nbLine++;
            
            int[] topStep = new int[Convert.ToInt32(nbLine)];
            int[] leftStep = new int[nbColumn];

            for (int i = 1; i < topStep.Length + 1; i++)
            {
                topStep[i - 1] = i * pnlMenus.Height / (nbLine + 1) - btn.Height / 2;
            }

            for (int i = 1; i < leftStep.Length + 1; i++)
            {
                leftStep[i - 1] = i * pnlMenus.Width / (nbColumn + 1);
            }

            int currentLine = 0;
            for (int i = 0; i < nbElem; i++)
            {
                btn = new Button();
                btn.Name = Convert.ToString(i);
                btn.Click += new EventHandler(btn_Click);
                                
                btn.Text = items[i].Id.Trim();
                if (btn.Text.Length * 7 > btn.Width)
                    btn.Width = btn.Text.Length * 7;

                btn.Top = topStep[currentLine];
                btn.Left = leftStep[i - (currentLine * nbColumn)] - btn.Width / 2;

                pnlMenus.Controls.Add(btn);

                if ((i + 1) % nbColumn == 0)
                    currentLine++;
            }

            pnlMenus.Visible = true;
        }

        /// <summary>
        /// Stop background worker
        /// </summary>
        private void StopJob()
        {
            canceledJob = true;
            m_UpTextBox(m_log.Log, resource.GetString("$Cancel")); 
            backgroundWorker1.CancelAsync();
        }

        /// <summary>
        /// Start background worker
        /// </summary>
        /// <param name="options">List of switches selected</param>
        private void StartJob(List<String> options)
        {
            m_UpTextBox(m_log.Log, "--------------------------------------------");
            m_UpTextBox(m_log.Log, resource.GetString("$Start"));
            m_total.Start();
            m_step.Start();
            List<Step> steps = new List<Step>();

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

        /// <summary>
        /// Display success download message with time to do it
        /// </summary>
        /// <param name="message"></param>
        private void Display_Message(string message)
        {
            m_step.Stop();
            ModifTextBox(m_log.Log, message + " " + resource.GetString("$DlTime") + " " + m_step.ElapsedMilliseconds + " ms");
            m_step.Reset();
            m_step.Start();
        }

        /// <summary>
        /// Move all file from temp folder to SD card
        /// </summary>
        private void UploadToSd()
        {
            if (MessageBox.Show(resource.GetString("$Move"),
                                resource.GetString("$Success"),
                                MessageBoxButtons.YesNo,
                                MessageBoxIcon.Question) == DialogResult.Yes)
                if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
                {
                    String sdRoot = folderBrowserDialog1.SelectedPath;
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
                        
                        MessageBox.Show(resource.GetString("$MoveS"),
                                        resource.GetString("$Success"),
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(resource.GetString("$MoveE") + ex.Message,
                                resource.GetString("$Error"),
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
                    }
                }
        }

        /// <summary>
        /// Clean temp file on computer
        /// </summary>
        private void CleanTemp()
        {
            if (MessageBox.Show(resource.GetString("$Clean"),
                                resource.GetString("$Success"),
                                MessageBoxButtons.YesNo,
                                MessageBoxIcon.Question) == DialogResult.Yes)
            {
                try
                {
                    foreach (FileInfo toDel in new DirectoryInfo(directory).GetFiles("*", SearchOption.AllDirectories))
                    {
                        toDel.Delete();
                    }
                    
                    MessageBox.Show(resource.GetString("$CleanS"),
                                            resource.GetString("$Success"),
                                            MessageBoxButtons.OK,
                                            MessageBoxIcon.Information);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(resource.GetString("$CleanE") + ex.Message,
                            resource.GetString("$Error"),
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                }
            }

        }
        #endregion

        #region public
        public MainFormV5(SciifiiConfiguration datas, String fileName)
        {
            InitializeComponent();

            m_taskFact = new TaskFactory();
            //Register downloader message event
            if (m_taskFact.message == null)
                m_taskFact.message += new MessageEventHandler(Display_Message);
            
            //Register delegate to update textbox with thread
            m_UpTextBox = new UpdateTextBoxDelegate(this.UpdateTextBox);

            m_log.Log.Text = "";

            //Call 2 time to display and mask log form use this enable invoking form
            btnLog_Click(null, EventArgs.Empty);
            btnLog_Click(null, EventArgs.Empty);

            hiddenOptions = new List<string>();

            this.fileName = fileName;
            
            this.datas = datas;
            if(datas != null)
                UpdateTextBox(m_log.Log, "config.xml v" + datas.Version + " " + resource.GetString("$LoadS"));

            DisplayMainMenu(datas.Menus, 4);
        }
        #endregion

        #region events
        /// <summary>
        /// Manage click on menu
        /// </summary>
        protected void menuStrip_ItemClicked(object sender, EventArgs e)
        {
            switch (((ToolStripDropDownItem)sender).Name)
            {
                case "msEdit":
                    new EditForm(datas, fileName).Show(this);
                    break;
                case "msQuit":
                    this.Close();
                    break;
                case "msWeb":
                    Process.Start("http://www.teamwiigen.fr.cr/");
                    break;
                case "msAbout":
                    new AboutForm().Show(this);
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// Show / Mask log form
        /// </summary>
        protected void btnLog_Click(object sender, EventArgs e)
        {
            if (m_log.Visible)
                m_log.Visible = false;
            else
            {
                //Display log at center right of main form
                m_log.Top = this.Top + (this.Height - m_log.Height) / 2;
                m_log.Left = this.Left + this.Width;

                m_log.Show();
            }
        }
        
        /// <summary>
        /// Display Mode menu or switch items
        /// </summary>
        protected void btn_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;

            //Get menu from xml
            SciifiiDTO.Menu.Menu selectedMenu = datas.Menus[Convert.ToInt32(btn.Name)];

            if (selectedMenu.ModeMenuItem.Count != 0)
                DisplaySecondMenu(selectedMenu.ModeMenuItem, 1);
            else if (selectedMenu.SwitchMenuItem.Count != 0)
                DisplayAdvancedMenu(selectedMenu.SwitchMenuItem, 3);
            else
                MessageBox.Show(resource.GetString("$MenuE"), resource.GetString("$Error"), MessageBoxButtons.OK);
        }

        /// <summary>
        /// Return to main menu
        /// </summary>
        protected void btn_ExitClick(object sender, EventArgs e)
        {
            DisplayMainMenu(datas.Menus, 4);
        }

        /// <summary>
        /// Launch download
        /// </summary>
        protected void btnDownload_Click(object sender, EventArgs e)
        {
            List<String> switches = new List<String>();
            
            Button btn = sender as Button;

            if (btn.Name == "¤advanced¤")
            {
                foreach (Control ctrl in pnlModeMenu.Controls)
                {
                    if (ctrl is CheckBox)
                    {
                        CheckBox cb = ctrl as CheckBox;
                        if (cb.Checked)
                            switches.Add(((CheckBox)ctrl).Name);
                    }
                }
            }
            else
                switches.AddRange(btn.Name.Split("|".ToCharArray(), StringSplitOptions.RemoveEmptyEntries));

            if (switches.Count == 0)
            {
                MessageBox.Show(resource.GetString("$NoWork"), resource.GetString("$Error"), MessageBoxButtons.OK);
            }
            else
            {
                if (!job)
                {
                    FolderBrowserDialog dial = new FolderBrowserDialog();
                    if (dial.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        directory = dial.SelectedPath;
                        StartJob(switches);
                    }
                }
            }
        }

        /// <summary>
        /// Stop download
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            if (job)
                StopJob();

            btnCancel.Enabled = false;
        }

        /// <summary>
        /// Start event from background worker
        /// </summary>
        protected void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            job = true;
            canceledJob = false;
            this.Invoke(new MethodInvoker(delegate()
            {
                try
                {
                    pnlModeMenu.Controls["¤advanced¤"].Enabled = false;
                }
                catch{}
                pnlModeMenu.Controls[Convert.ToString(resource.GetString("$Exit"))].Enabled = false;
                btnCancel.Enabled = btnCancel.Visible = true;
            }));      
            
            Directory.CreateDirectory(directory);
            CompositeInstaller container = new CompositeInstaller();

            foreach (Step s in (IEnumerable<Step>)e.Argument)
                container.Steps.Add(s);

            m_taskFact.CreateTask(container).Prepare(directory, datas, (BackgroundWorker)sender, e, 0, container.StepsFullCount);
        }

        /// <summary>
        /// Progress event from background worker used to display in progress bar
        /// </summary>
        protected void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            pbStatus.Value = e.ProgressPercentage;
        }

        /// <summary>
        /// Finished event from backgroud worker, display message and call method to send file on SD card
        /// </summary>
        protected void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            m_total.Stop();
            UpdateTextBox(m_log.Log, "--------------------------------------------");
            UpdateTextBox(m_log.Log, resource.GetString("$DlEnd") + " " + (m_total.ElapsedMilliseconds / 1000) + " s");
            UpdateTextBox(m_log.Log, "--------------------------------------------");

            pbStatus.Value = 0;
            
            if (e.Error != null)
                UpdateTextBox(m_log.Log, resource.GetString("$ErrorS") + "\n" + e.Error.Message);

            job = false;
            this.Invoke(new MethodInvoker(delegate()
            {
                btnCancel.Visible = false;
                try
                {
                    pnlModeMenu.Controls["¤advanced¤"].Enabled = true;
                }
                catch{}
                pnlModeMenu.Controls[Convert.ToString(resource.GetString("$Exit"))].Enabled = true;
            }));   

            if (e.Error == null && !canceledJob)
                UploadToSd();

            if (canceledJob)
                CleanTemp();
        }
        #endregion

        #region ControlManagment
        private delegate void UpdateTextBoxDelegate(System.Windows.Forms.TextBox tb, String value);
        private UpdateTextBoxDelegate m_UpTextBox;

        private void UpdateTextBox(System.Windows.Forms.TextBox tb, String value)
        {
            value = DateTime.Now.ToString(resource.GetString("$TimeFormat")) + " : " + value;
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
