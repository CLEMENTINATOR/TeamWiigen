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
            this.SuspendLayout();
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
            // MainFormV5
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Sciifii.Properties.Resources.advanced_screen;
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.pnlModeMenu);
            this.Controls.Add(this.btnLog);
            this.Controls.Add(this.pbStatus);
            this.Controls.Add(this.pnlMenus);
            this.MaximizeBox = false;
            this.Name = "MainFormV5";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.ResumeLayout(false);

        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Panel pnlMenus;
        private System.Windows.Forms.ProgressBar pbStatus;
        private System.Windows.Forms.Button btnLog;
        private System.Windows.Forms.Panel pnlModeMenu;
        private System.Windows.Forms.Button btnCancel;

    }
}