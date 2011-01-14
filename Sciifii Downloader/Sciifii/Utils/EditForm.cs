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
using System.Resources;
using SciifiiDTO.Corp;

namespace Sciifii.Utils
{
    public partial class EditForm : Form
    {
        #region private
        private SciifiiConfiguration datas;
        private SciifiiConfiguration datasBackup;
        private String fileName;

        ResourceManager resource = new ResourceManager(typeof(EditForm));

        private void LoadFiles(TreeNode root)
        {
            string filesNodeName = "files";
            
            TreeNode treeFiles = root.Nodes.Add(filesNodeName, filesNodeName);
            foreach (ManagedFile file in datas.ManagedFiles)
                treeFiles.Nodes.Add(file.Key, file.Key);
        }

        private void LoadMenus(TreeNode root)
        {
            string menusNodeName = "menus";
            
            TreeNode treeMenus = root.Nodes.Add(menusNodeName, menusNodeName);
            foreach (SciifiiDTO.Menu.Menu menu in datas.Menus)
            {
                TreeNode treeMenu = treeMenus.Nodes.Add(menu.Id, menu.Id);
                foreach (ModeMenuItem mode in menu.ModeMenuItem)
                    treeMenu.Nodes.Add(mode.Text, mode.Text);

                foreach (SwitchMenuItem switc in menu.SwitchMenuItem)
                    treeMenu.Nodes.Add(switc.Text, switc.Text);

                int nbSeparator = 0;
                foreach(SeparatorMenuItem separator in menu.SeparatorMenuItem)
                {
                    treeMenu.Nodes.Add("separatorMenuItem" + nbSeparator, "separatorMenuItem" + nbSeparator);
                    nbSeparator++;
                }

                int nbNavigation = 0;
                foreach (NavigationMenuItem separator in menu.NavigationMenuItem)
                {
                    treeMenu.Nodes.Add("navigationMenuItem" + nbNavigation, "navigationMenuItem" + nbNavigation);
                    nbNavigation++;
                }

                int nbPrevious = 0;
                foreach (PreviousMenuItem separator in menu.PreviousMenuItem)
                {
                    treeMenu.Nodes.Add("previousMenuItem" + nbPrevious, "previousMenuItem" + nbPrevious);
                    nbPrevious++;
                }

                int nbStart = 0;
                foreach (StartMenuItem separator in menu.StartMenuItem)
                {
                    treeMenu.Nodes.Add("startMenuItem" + nbStart, "startMenuItem" + nbStart);
                    nbStart++;
                }

                int nbExit = 0;
                foreach (ExitMenuItem separator in menu.ExitMenuItem)
                {
                    treeMenu.Nodes.Add("exitMenuItem" + nbExit, "exitMenuItem" + nbExit);
                    nbExit++;
                }
            }
        }

        #region stepLoading
        private void LoadCiosCorp(TreeNode ciosCorpRoot, CiosCorp step)
        {
            int nbItems = 0;
            foreach (CorpItem item in step.Items)
            {
                ciosCorpRoot.Nodes.Add("item" + nbItems, "item" + nbItems);
                nbItems++;
            }

            foreach (CorpModule module in step.Modules)
                ciosCorpRoot.Nodes.Add(module.Name, module.Name);
        }

        private void LoadCiosInstaller(TreeNode ciosInstallerRoot, CiosInstaller step)
        {

        }

        private void LoadCompositeInstaller(TreeNode compositeInstallerRoot, CompositeInstaller step)
        {

        }

        private void LoadFileDownloader(TreeNode fileDownloaderRoot, FileDownloader step)
        {

        }

        private void LoadFileSystemTask(TreeNode fileSystemtaskRoot, FileSystemTask step)
        {

        }

        private void LoadIdentifier(TreeNode identifierRoot, Identifier step)
        {

        }

        private void LoadIOSReloader(TreeNode iosReloaderRoot, IOSReloader step)
        {

        }

        private void LoadMemoryPatcher(TreeNode memoryPatcherRoot, MemoryPatcher step)
        {

        }

        private void LoadPreloader(TreeNode preloaderRoot, Preloader step)
        {

        }

        private void LoadTitleInstaller(TreeNode titleInstallerRoot, TitleInstaller step)
        {

        }

        private void LoadTitleDowngrader(TreeNode titleDowngraderRoot, TitleDowngrader step)
        {

        }

        private void LoadWadBatchInstaller(TreeNode wadBatchInstallerRoot, WadBatchInstaller step)
        {

        }

        private void LoadSteps(TreeNode root)
        {
            string stepsNodeName = "steps";

            TreeNode treeSteps = root.Nodes.Add(stepsNodeName, stepsNodeName);

            int nbCiosCorp = 0;
            int nbCiosInstaller = 0;
            int nbCompositeInstaller = 0;
            int nbFileDownloader = 0;
            int nbFileSystemTask = 0;
            int nbIdentifier = 0;
            int nbIOSReloader = 0;
            int nbMemoryPatcher = 0;
            int nbPreloader = 0;
            int nbTitleInstaller = 0;
            int nbTitleDowngrader = 0;
            int nbWadBatchInstaller = 0;
            foreach (Step step in datas.Steps)
            {
                switch (step.GetType().Name)
                {
                    case "CiosCorp":
                        LoadCiosCorp(treeSteps.Nodes.Add("CiosCorp" + nbCiosCorp, "CiosCorp" + nbCiosCorp), step as CiosCorp);
                        nbCiosCorp++;
                        break;
                    case "CiosInstaller":
                        LoadCiosInstaller(treeSteps.Nodes.Add("CiosInstaller" + nbCiosInstaller, "CiosInstaller" + nbCiosInstaller), step as CiosInstaller);
                        nbCiosInstaller++;
                        break;
                    case "CompositeInstaller":
                        LoadCompositeInstaller(treeSteps.Nodes.Add("CompositeInstaller" + nbCompositeInstaller, "CompositeInstaller" + nbCompositeInstaller), step as CompositeInstaller);
                        nbCompositeInstaller++;
                        break;
                    case "FileDownloader":
                        LoadFileDownloader(treeSteps.Nodes.Add("FileDownloader" + nbFileDownloader, "FileDownloader" + nbFileDownloader), step as FileDownloader);
                        nbFileDownloader++;
                        break;
                    case "FileSystemTask":
                        LoadFileSystemTask(treeSteps.Nodes.Add("FileSystemTask" + nbFileSystemTask, "FileSystemTask" + nbFileSystemTask), step as FileSystemTask);
                        nbFileSystemTask++;
                        break;
                    case "Identifier":
                        LoadIdentifier(treeSteps.Nodes.Add("Identifier" + nbIdentifier, "Identifier" + nbIdentifier), step as Identifier);
                        nbIdentifier++;
                        break;
                    case "IOSReloader":
                        LoadIOSReloader(treeSteps.Nodes.Add("IOSReloader" + nbIOSReloader, "IOSReloader" + nbIOSReloader), step as IOSReloader);
                        nbIOSReloader++;
                        break;
                    case "MemoryPatcher":
                        LoadMemoryPatcher(treeSteps.Nodes.Add("MemoryPatcher" + nbMemoryPatcher, "MemoryPatcher" + nbMemoryPatcher), step as MemoryPatcher);
                        nbMemoryPatcher++;
                        break;
                    case "Preloader":
                        LoadPreloader(treeSteps.Nodes.Add("Preloader" + nbPreloader, "Preloader" + nbPreloader), step as Preloader);
                        nbPreloader++;
                        break;
                    case "TitleInstaller":
                        LoadTitleInstaller(treeSteps.Nodes.Add("TitleInstaller" + nbTitleInstaller, "TitleInstaller" + nbTitleInstaller), step as TitleInstaller);
                        nbTitleInstaller++;
                        break;
                    case "TitleDowngrader":
                        LoadTitleDowngrader(treeSteps.Nodes.Add("TitleDowngrader" + nbTitleDowngrader, "TitleDowngrader" + nbTitleDowngrader), step as TitleDowngrader);
                        nbTitleDowngrader++;
                        break;
                    case "WadBatchInstaller":
                        LoadWadBatchInstaller(treeSteps.Nodes.Add("WadBatchInstaller" + nbWadBatchInstaller, "WadBatchInstaller" + nbWadBatchInstaller), step as WadBatchInstaller);
                        nbWadBatchInstaller++;
                        break;
                    default:
                        throw new InvalidCastException();                 
                }
            }
        }
        #endregion

        private void LoadLogs(TreeNode root)
        {
            string logsNodeName = "logs";

            TreeNode treeLogs = root.Nodes.Add(logsNodeName, logsNodeName);

            int nbLog = 0;
            foreach (SciifiiDTO.Log.Log log in datas.Logs)
            {
                treeLogs.Nodes.Add("log" + nbLog, "log" + nbLog);
                nbLog++;
            }
        }
        
        private void LoadDisclaimer(TreeNode root)
        {
            string disclaimerNodeName = "disclaimer";

            root.Nodes.Add(disclaimerNodeName, disclaimerNodeName);
        }

        /// <summary>
        /// Add main node 'sciifii' to treeview and call all load method
        /// </summary>
        private void LoadTreeView()
        {
            TreeNode root = treeView.Nodes.Add("sciifii", "sciifii");
            
            LoadFiles(root);
            LoadSteps(root);
            LoadMenus(root);

            LoadLogs(root);
            LoadDisclaimer(root);
        }
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
        /// <summary>
        /// When form shown load data
        /// </summary>
        private void EditForm_Shown(object sender, EventArgs e)
        {
            LoadTreeView();
        }

        /// <summary>
        /// Check if configuration updated, ask for saving and ave in config.xml
        /// </summary>
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
