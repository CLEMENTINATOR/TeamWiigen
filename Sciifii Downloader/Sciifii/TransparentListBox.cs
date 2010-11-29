using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sciifii
{
    public class TransparentListBox : System.Windows.Forms.ListBox
    {
        public TransparentListBox()
        {
            base.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
        }
    }
}
