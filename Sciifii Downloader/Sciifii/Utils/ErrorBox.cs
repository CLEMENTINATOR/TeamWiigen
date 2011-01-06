using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sciifii.Utils
{
    public partial class ErrorBox : Form
    {
        public ErrorBox()
        {
            InitializeComponent();
        }

        public ErrorBox(string title, Exception E)
        {
            InitializeComponent();

            tbError.Text = "Inner Exception\r\n--------------------------------------------------------------------------\r\n" +
                E.InnerException +
                "\r\nStack Trace\r\n--------------------------------------------------------------------------\r\n\r\n" +
                E.StackTrace;
        }

        public static void Show(Exception e)
        {
            ErrorBox eb = new ErrorBox(Application.ProductName, e);
            eb.ShowDialog();
        }

        protected void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
