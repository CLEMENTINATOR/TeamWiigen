using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Sciifii.DTO.Steps;
using Sciifii.DTO;
using Sciifii.DTO.Menus;
using System.Collections.ObjectModel;
using System.Windows.Input;
using Sciifii.Downloader.Tools;
using Sciifii.Business;
using WinForms = System.Windows.Forms;
using System.IO;

namespace Sciifii.Downloader.ViewModel
{
    public class MenuViewModel : INotifyPropertyChanged
    {
        BackgroundWorker worker;
        TaskFactory factory;

        public MenuViewModel()
        {
            worker = new BackgroundWorker();
            worker.WorkerReportsProgress = true;
            worker.WorkerSupportsCancellation = true;
            worker.DoWork += backgroundWorker1_DoWork;
            worker.ProgressChanged += backgroundWorker1_ProgressChanged;
            worker.RunWorkerCompleted += backgroundWorker1_RunWorkerCompleted;

            factory = new TaskFactory();
            factory.message += new MessageEventHandler(factory_message);

            EnablePopUpButton = true;
            Message = "Sciifii is analysing your choice!";

            //setting default values
            PopUpButtonMessage = "Cancel";
            AvailableRegions = new ObservableCollection<StepRegion>();
            foreach (StepRegion region in Enum.GetValues(typeof(StepRegion)))
                AvailableRegions.Add(region);
            SelectedRegion = StepRegion.Europe;

            showPopUp = System.Windows.Visibility.Collapsed;
            menuPath = new Stack<string>();

            //create commands
            ExitCommand = new RelayCommand(param => Exit(param));
            NavigateCommand = new RelayCommand(param => Navigate(param));
            ModeCommand = new RelayCommand(param => Mode(param));
            SwitchCommand = new RelayCommand(param => Switch(param));
            StartCommand = new RelayCommand(param => Start(param));
            ValidateDownloadCommand = new RelayCommand(param => ValidateDownload(param));
            Navigate();
        }

        #region Properties

        private ObservableCollection<MenuItem> currentMenuItems;
        public ObservableCollection<MenuItem> CurrentMenuItems
        {
            get { return currentMenuItems; }
            private set
            {
                currentMenuItems = value;
                OnPropertyChanged("CurrentMenuItems");
            }
        }

        private Stack<string> menuPath;

        private System.Windows.Visibility showPopUp;
        public System.Windows.Visibility ShowPopUp
        {
            get
            {
                return showPopUp;
            }

            set
            {
                showPopUp = value;
                OnPropertyChanged("ShowPopUp");
            }
        }

        private int progression;
        public int Progression
        {
            get
            {
                return progression;
            }

            set
            {
                progression = value;
                OnPropertyChanged("Progression");
            }
        }

        private string message;
        public string Message
        {
            get
            {
                return message;
            }

            set
            {
                message = value;
                OnPropertyChanged("Message");
            }
        }

        private bool enablePopUpButton;
        public bool EnablePopUpButton
        {
            get
            {
                return enablePopUpButton;
            }

            set
            {
                enablePopUpButton = value;
                OnPropertyChanged("EnablePopUpButton");
            }
        }

        private string popUpButtonMessage;
        public string PopUpButtonMessage
        {
            get { return popUpButtonMessage; }
            set
            {
                popUpButtonMessage = value;
                OnPropertyChanged("PopUpButtonMessage");
            }
        }

        private ObservableCollection<StepRegion> availableRegions;

        public ObservableCollection<StepRegion> AvailableRegions
        {
            get { return availableRegions; }
            set
            {
                availableRegions = value;
                OnPropertyChanged("AvailableRegions");
            }
        }

        public StepRegion SelectedRegion
        {
            get { return Configuration.Current.SelectedRegion; }
            set
            {
                Configuration.Current.SelectedRegion = value;
                OnPropertyChanged("SelectedRegion");
            }
        }

        #endregion

        #region Commands

        public ICommand ExitCommand { get; private set; }
        private void Exit(object param)
        {
            System.Windows.Application.Current.MainWindow.Close();
        }

        public ICommand NavigateCommand { get; private set; }
        private void Navigate(object param = null)
        {
            ObservableCollection<MenuItem> items;

            if (CurrentMenuItems != null)
                CurrentMenuItems.Clear();

            if (param == null)
            {
                Menu menu = Configuration.Current.MenuCollection[Configuration.Current.MenuCollection.StartMenuId];
                menuPath.Push(Configuration.Current.MenuCollection.StartMenuId);
                items = (menu == null ? new ObservableCollection<MenuItem>() : new ObservableCollection<MenuItem>(menu.Items));
            }
            else
            {
                NavigationMenuItem item = param as NavigationMenuItem;

                if (item.MenuId.Equals(".."))
                {
                    menuPath.Pop();
                    Menu menu = Configuration.Current.MenuCollection[menuPath.Peek()];
                    items = (menu == null ? new ObservableCollection<MenuItem>() : new ObservableCollection<MenuItem>(menu.Items));
                }
                else
                {
                    Menu menu = Configuration.Current.MenuCollection[item.MenuId];
                    menuPath.Push(item.MenuId);
                    items = (menu == null ? new ObservableCollection<MenuItem>() : new ObservableCollection<MenuItem>(menu.Items));
                }

                Configuration.Current.ValidateSwitchSelection(item.SaveOptions);
            }

            CurrentMenuItems = items;
        }

        public ICommand ModeCommand { get; private set; }
        private void Mode(object param)
        {
            Configuration.Current.SetMode(param as List<string>);
            ExecuteDownload();
        }

        public ICommand SwitchCommand { get; private set; }
        private void Switch(object param)
        {
            Configuration.Current.ModifySwitchStatus(param as String);
        }

        public ICommand StartCommand { get; private set; }
        private void Start(object param)
        {
            Configuration.Current.ValidateSwitchSelection((bool)param);
            ExecuteDownload();
        }

        public ICommand UpCommand { get; private set; }

        public ICommand DownCommand { get; private set; }

        public ICommand ValidateDownloadCommand { get; private set; }
        private void ValidateDownload(object param)
        {
            if (worker.IsBusy)
            {
                worker.CancelAsync();
                EnablePopUpButton = false;
                PopUpButtonMessage = "Canceling";
            }
            else
                Exit(null);
        }
        #endregion

        #region INotifyPropertyChanged

        protected void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        private void ExecuteDownload()
        {
            WinForms.FolderBrowserDialog dial = new WinForms.FolderBrowserDialog();
            dial.Description = "Select your sd or a folder where you want to download the files";

            if (dial.ShowDialog() == WinForms.DialogResult.OK)
                worker.RunWorkerAsync(dial.SelectedPath);
        }

        void factory_message(string message)
        {
            Message = message;
        }

        protected void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            ShowPopUp = System.Windows.Visibility.Visible;

            Directory.CreateDirectory(e.Argument.ToString());
            CompositeInstaller container = new CompositeInstaller();

            foreach (BaseStep s in Configuration.Current.ActiveSteps)
                container.Steps.Add(s);

            factory.CreateTask(container).Prepare(e.Argument.ToString(), (BackgroundWorker)sender, e, 0, container.StepsFullCount);
        }

        protected void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            Progression = e.ProgressPercentage;
        }

        protected void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                System.Windows.Forms.MessageBox.Show(e.Error.StackTrace, e.Error.Message, WinForms.MessageBoxButtons.OK, WinForms.MessageBoxIcon.Error);
                ExitCommand.Execute(null);
            }

            if (PopUpButtonMessage == "Canceling")
                Message = "Canceled!";
            else
                Message = "Job done!";

            PopUpButtonMessage = "Exit";
            EnablePopUpButton = true;
        }
    }
}
