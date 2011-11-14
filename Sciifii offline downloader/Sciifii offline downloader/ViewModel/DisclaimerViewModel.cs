using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Sciifii.DTO;
using System.Windows.Input;
using Sciifii.Downloader.Tools;

namespace Sciifii.Downloader.ViewModel
{
    public class DisclaimerViewModel : INotifyPropertyChanged
    {
        public DisclaimerViewModel()
        {
            Configuration config = Configuration.LoadConfiguration();
            Text = config.Disclaimer;
            ContinueCommand = new RelayCommand(param => Continue(param));
            ExitCommand = new RelayCommand(p => System.Windows.Application.Current.MainWindow.Close());
        }

        private string text;
        public string Text
        {
            get
            {
                return text;
            }

            set
            {
                text = value;
                OnPropertyChanged("Text");
            }
        }

        #region CommandHandlers

        public ICommand ContinueCommand { get; private set; }
        private void Continue( object param)
        {
            ApplicationHelper.NavigationService.Navigate(new Uri("Views/MenuView.xaml", UriKind.RelativeOrAbsolute));
        }

        public ICommand ExitCommand { get; private set; }

        #endregion
  
        #region INotifyPropertyChanged
        protected void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion
    }
}
