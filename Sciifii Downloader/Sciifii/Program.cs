using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Sciifii
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Use old new
            //Application.Run(new MainForm());
            //Use old form
            Application.Run(new Form1());
        }
    }
}
