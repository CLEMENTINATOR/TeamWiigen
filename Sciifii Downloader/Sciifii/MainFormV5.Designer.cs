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
            this.tbStatus = new System.Windows.Forms.TextBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.btnDownload = new System.Windows.Forms.Button();
            this.pnlMenus = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // tbStatus
            // 
            this.tbStatus.BackColor = System.Drawing.SystemColors.WindowText;
            this.tbStatus.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Bold);
            this.tbStatus.ForeColor = System.Drawing.Color.DeepSkyBlue;
            this.tbStatus.Location = new System.Drawing.Point(12, 416);
            this.tbStatus.Multiline = true;
            this.tbStatus.Name = "tbStatus";
            this.tbStatus.ReadOnly = true;
            this.tbStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbStatus.Size = new System.Drawing.Size(615, 49);
            this.tbStatus.TabIndex = 0;
            // 
            // btnDownload
            // 
            this.btnDownload.Location = new System.Drawing.Point(797, 10);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(75, 23);
            this.btnDownload.TabIndex = 3;
            this.btnDownload.Text = "Download";
            this.btnDownload.UseVisualStyleBackColor = true;
            // 
            // pnlMenus
            // 
            this.pnlMenus.BackColor = System.Drawing.Color.Transparent;
            this.pnlMenus.Location = new System.Drawing.Point(46, 145);
            this.pnlMenus.Name = "pnlMenus";
            this.pnlMenus.Size = new System.Drawing.Size(550, 230);
            this.pnlMenus.TabIndex = 4;
            // 
            // MainFormV5
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Sciifii.Properties.Resources.advanced_screen;
            this.ClientSize = new System.Drawing.Size(639, 477);
            this.Controls.Add(this.pnlMenus);
            this.Controls.Add(this.btnDownload);
            this.Controls.Add(this.tbStatus);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(655, 515);
            this.MinimumSize = new System.Drawing.Size(655, 515);
            this.Name = "MainFormV5";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Sciifii downloader";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbStatus;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.Panel pnlMenus;

    }
}