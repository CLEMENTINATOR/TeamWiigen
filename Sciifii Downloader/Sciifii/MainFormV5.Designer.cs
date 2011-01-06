namespace Sciifii
{
    partial class MainFormV5
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainFormV5));
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.pnlMenus = new System.Windows.Forms.Panel();
            this.pbStatus = new System.Windows.Forms.ProgressBar();
            this.btnLog = new System.Windows.Forms.Button();
            this.pnlModeMenu = new System.Windows.Forms.Panel();
            this.btnCancel = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.msEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.msQuit = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.msWeb = new System.Windows.Forms.ToolStripMenuItem();
            this.msAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
            this.backgroundWorker1.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker1_RunWorkerCompleted);
            // 
            // pnlMenus
            // 
            this.pnlMenus.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.pnlMenus, "pnlMenus");
            this.pnlMenus.Name = "pnlMenus";
            // 
            // pbStatus
            // 
            resources.ApplyResources(this.pbStatus, "pbStatus");
            this.pbStatus.Name = "pbStatus";
            // 
            // btnLog
            // 
            resources.ApplyResources(this.btnLog, "btnLog");
            this.btnLog.Name = "btnLog";
            this.btnLog.UseVisualStyleBackColor = true;
            this.btnLog.Click += new System.EventHandler(this.btnLog_Click);
            // 
            // pnlModeMenu
            // 
            this.pnlModeMenu.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.pnlModeMenu, "pnlModeMenu");
            this.pnlModeMenu.Name = "pnlModeMenu";
            // 
            // btnCancel
            // 
            resources.ApplyResources(this.btnCancel, "btnCancel");
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.toolStripMenuItem1});
            resources.ApplyResources(this.menuStrip1, "menuStrip1");
            this.menuStrip1.Name = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.msEdit,
            this.msQuit});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            resources.ApplyResources(this.fichierToolStripMenuItem, "fichierToolStripMenuItem");
            // 
            // msEdit
            // 
            this.msEdit.Name = "msEdit";
            resources.ApplyResources(this.msEdit, "msEdit");
            this.msEdit.Click += new System.EventHandler(this.menuStrip_ItemClicked);
            // 
            // msQuit
            // 
            this.msQuit.Name = "msQuit";
            resources.ApplyResources(this.msQuit, "msQuit");
            this.msQuit.Click += new System.EventHandler(this.menuStrip_ItemClicked);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.msWeb,
            this.msAbout});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            resources.ApplyResources(this.toolStripMenuItem1, "toolStripMenuItem1");
            // 
            // msWeb
            // 
            this.msWeb.Name = "msWeb";
            resources.ApplyResources(this.msWeb, "msWeb");
            this.msWeb.Click += new System.EventHandler(this.menuStrip_ItemClicked);
            // 
            // msAbout
            // 
            this.msAbout.Name = "msAbout";
            resources.ApplyResources(this.msAbout, "msAbout");
            this.msAbout.Click += new System.EventHandler(this.menuStrip_ItemClicked);
            // 
            // MainFormV5
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Sciifii.Properties.Resources.advanced_screen;
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.pnlModeMenu);
            this.Controls.Add(this.btnLog);
            this.Controls.Add(this.pbStatus);
            this.Controls.Add(this.pnlMenus);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "MainFormV5";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Panel pnlMenus;
        private System.Windows.Forms.ProgressBar pbStatus;
        private System.Windows.Forms.Button btnLog;
        private System.Windows.Forms.Panel pnlModeMenu;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem msEdit;
        private System.Windows.Forms.ToolStripMenuItem msQuit;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem msWeb;
        private System.Windows.Forms.ToolStripMenuItem msAbout;

    }
}