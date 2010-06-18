namespace Sciifii
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.lbMode = new System.Windows.Forms.ListBox();
            this.sciifiiModeBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.tbStatus = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.clbOption = new System.Windows.Forms.CheckedListBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.pbStatus = new System.Windows.Forms.ToolStripProgressBar();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.btnDownload = new System.Windows.Forms.Button();
            this.ddlRegion = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.sciifiiModeBindingSource)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "Fichier config.xml|config.xml";
            // 
            // lbMode
            // 
            this.lbMode.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.lbMode.DataSource = this.sciifiiModeBindingSource;
            this.lbMode.DisplayMember = "Text";
            this.lbMode.FormattingEnabled = true;
            this.lbMode.Location = new System.Drawing.Point(6, 27);
            this.lbMode.Name = "lbMode";
            this.lbMode.Size = new System.Drawing.Size(188, 238);
            this.lbMode.TabIndex = 0;
            this.lbMode.ValueMember = "options";
            this.lbMode.SelectedIndexChanged += new System.EventHandler(this.lbMode_SelectedIndexChanged);
            // 
            // sciifiiModeBindingSource
            // 
            this.sciifiiModeBindingSource.DataSource = typeof(SciifiiDTO.Mode);
            // 
            // tbStatus
            // 
            this.tbStatus.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbStatus.BackColor = System.Drawing.SystemColors.WindowText;
            this.tbStatus.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbStatus.ForeColor = System.Drawing.Color.DeepSkyBlue;
            this.tbStatus.Location = new System.Drawing.Point(424, 36);
            this.tbStatus.Multiline = true;
            this.tbStatus.Name = "tbStatus";
            this.tbStatus.ReadOnly = true;
            this.tbStatus.Size = new System.Drawing.Size(200, 244);
            this.tbStatus.TabIndex = 10;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBox1.Controls.Add(this.lbMode);
            this.groupBox1.Controls.Add(this.clbOption);
            this.groupBox1.Location = new System.Drawing.Point(12, 9);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(406, 271);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Select mode:";
            // 
            // clbOption
            // 
            this.clbOption.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.clbOption.BackColor = System.Drawing.SystemColors.Control;
            this.clbOption.CheckOnClick = true;
            this.clbOption.FormattingEnabled = true;
            this.clbOption.Location = new System.Drawing.Point(200, 21);
            this.clbOption.Name = "clbOption";
            this.clbOption.Size = new System.Drawing.Size(200, 244);
            this.clbOption.TabIndex = 1;
            this.clbOption.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.clbOption_ItemCheck);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.pbStatus});
            this.statusStrip1.Location = new System.Drawing.Point(0, 290);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(636, 22);
            this.statusStrip1.TabIndex = 5;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(55, 17);
            this.toolStripStatusLabel1.Text = "Progress:";
            // 
            // pbStatus
            // 
            this.pbStatus.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.pbStatus.Name = "pbStatus";
            this.pbStatus.Size = new System.Drawing.Size(525, 16);
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
            this.backgroundWorker1.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker1_RunWorkerCompleted);
            // 
            // btnDownload
            // 
            this.btnDownload.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnDownload.Location = new System.Drawing.Point(549, 7);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(75, 23);
            this.btnDownload.TabIndex = 3;
            this.btnDownload.Text = "Download";
            this.btnDownload.UseVisualStyleBackColor = true;
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // ddlRegion
            // 
            this.ddlRegion.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ddlRegion.FormattingEnabled = true;
            this.ddlRegion.Location = new System.Drawing.Point(424, 9);
            this.ddlRegion.Name = "ddlRegion";
            this.ddlRegion.Size = new System.Drawing.Size(49, 21);
            this.ddlRegion.TabIndex = 2;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(636, 312);
            this.Controls.Add(this.ddlRegion);
            this.Controls.Add(this.btnDownload);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tbStatus);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(652, 330);
            this.Name = "MainForm";
            this.Text = "Sciifii downloader";
            ((System.ComponentModel.ISupportInitialize)(this.sciifiiModeBindingSource)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ListBox lbMode;
        private System.Windows.Forms.TextBox tbStatus;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckedListBox clbOption;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripProgressBar pbStatus;
        private System.Windows.Forms.BindingSource sciifiiModeBindingSource;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.ComboBox ddlRegion;
    }
}