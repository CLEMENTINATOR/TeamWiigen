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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainFormV5));
            this.tbStatus = new System.Windows.Forms.TextBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.sciifiiModeBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.lbMenu = new Sciifii.TransparentListBox();
            this.clbOption = new System.Windows.Forms.CheckedListBox();
            this.btnDownload = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.sciifiiModeBindingSource)).BeginInit();
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
            // sciifiiModeBindingSource
            // 
            this.sciifiiModeBindingSource.DataSource = typeof(SciifiiDTO.Menu.Menu);
            // 
            // lbMenu
            // 
            this.lbMenu.BackColor = System.Drawing.Color.Transparent;
            this.lbMenu.DataSource = this.sciifiiModeBindingSource;
            this.lbMenu.DisplayMember = "Id";
            this.lbMenu.FormattingEnabled = true;
            this.lbMenu.Location = new System.Drawing.Point(84, 137);
            this.lbMenu.Name = "lbMenu";
            this.lbMenu.Size = new System.Drawing.Size(188, 238);
            this.lbMenu.TabIndex = 1;
            // 
            // clbOption
            // 
            this.clbOption.FormattingEnabled = true;
            this.clbOption.Location = new System.Drawing.Point(359, 137);
            this.clbOption.Name = "clbOption";
            this.clbOption.Size = new System.Drawing.Size(200, 244);
            this.clbOption.TabIndex = 2;
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
            // MainFormV5
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Sciifii.Properties.Resources.advanced_screen;
            this.ClientSize = new System.Drawing.Size(639, 477);
            this.Controls.Add(this.btnDownload);
            this.Controls.Add(this.clbOption);
            this.Controls.Add(this.lbMenu);
            this.Controls.Add(this.tbStatus);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(655, 515);
            this.MinimumSize = new System.Drawing.Size(655, 515);
            this.Name = "MainFormV5";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Sciifii downloader";
            ((System.ComponentModel.ISupportInitialize)(this.sciifiiModeBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbStatus;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.BindingSource sciifiiModeBindingSource;
        private TransparentListBox lbMenu;
        private System.Windows.Forms.CheckedListBox clbOption;
        private System.Windows.Forms.Button btnDownload;

    }
}