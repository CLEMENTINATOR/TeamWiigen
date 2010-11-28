using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SciifiiDTO;

namespace Sciifii
{
    public partial class MainFormV5 : Form
    {
        #region private
        private SciifiiConfiguration datas;
        #endregion

        #region public
        public MainFormV5(SciifiiConfiguration datas)
        {
            InitializeComponent();

            this.datas = datas;
            /*if (datas != null)
                UpdateTextBox(tbStatus, "Config.xml load with success.");*/
        }
        #endregion

        #region events
        #endregion
    }
}
