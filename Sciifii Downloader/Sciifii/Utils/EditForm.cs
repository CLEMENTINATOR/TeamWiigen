using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SciifiiDTO;
using System.IO;
using System.Xml.Serialization;
using SciifiiDTO.Menu;

namespace Sciifii.Utils
{
    public partial class EditForm : Form
    {
        #region private
        private SciifiiConfiguration datas;
        private SciifiiConfiguration datasBackup;
        private String fileName;
        #endregion

        #region public
        public EditForm(SciifiiConfiguration datas, String fileName)
        {
            InitializeComponent();

            this.datasBackup = this.datas = datas;
            this.fileName = fileName;
        }
        #endregion

        #region events
        private void EditForm_Shown(object sender, EventArgs e)
        {
            foreach (SciifiiDTO.Menu.Menu menu in datas.Menus)
            {
                treeView1.Nodes.Add(menu.Id);
                foreach(ModeMenuItem mode in menu.ModeMenuItem)
                    treeView1.Nodes[treeView1.Nodes.Count - 1].Nodes.Add(mode.Text);

                foreach(SwitchMenuItem switc in menu.SwitchMenuItem)
                    treeView1.Nodes[treeView1.Nodes.Count - 1].Nodes.Add(switc.Text);
            }
        }

        protected void EditForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (datas != datasBackup) // Only if configuration updated display message
            { 
                if(MessageBox.Show("Voulez-vous sauvegarder", "Configuration modifiée", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question) ==
                    System.Windows.Forms.DialogResult.Yes)
                {
                    using (Stream config = File.Open(fileName, FileMode.Open, FileAccess.Write))
                        new XmlSerializer(typeof(SciifiiConfiguration)).Serialize(config, datas);
                }
            }
        }
        #endregion
    }
}
