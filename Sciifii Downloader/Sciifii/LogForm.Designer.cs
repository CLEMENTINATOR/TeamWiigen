namespace Sciifii
{
    partial class LogForm
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
            this.tbStatus = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // tbStatus
            // 
            this.tbStatus.BackColor = System.Drawing.SystemColors.WindowText;
            this.tbStatus.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Bold);
            this.tbStatus.ForeColor = System.Drawing.Color.DeepSkyBlue;
            this.tbStatus.Location = new System.Drawing.Point(12, 12);
            this.tbStatus.Multiline = true;
            this.tbStatus.Name = "tbStatus";
            this.tbStatus.ReadOnly = true;
            this.tbStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbStatus.Size = new System.Drawing.Size(426, 326);
            this.tbStatus.TabIndex = 1;
            // 
            // LogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(450, 350);
            this.Controls.Add(this.tbStatus);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "LogForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "LogForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbStatus;
    }
}