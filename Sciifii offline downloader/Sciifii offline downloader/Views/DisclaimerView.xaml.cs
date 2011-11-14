using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Sciifii.Downloader.ViewModel;

namespace Sciifii.Downloader.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class DisclaimerView : Page
    {
        public DisclaimerView()
        {
            this.DataContext = new DisclaimerViewModel();
            InitializeComponent();
        }

        private void Thumb_DragDelta(object sender, System.Windows.Controls.Primitives.DragDeltaEventArgs e)
        {
            App.Current.MainWindow.Left += e.HorizontalChange;
            App.Current.MainWindow.Top += e.VerticalChange;
        }
    }
}
