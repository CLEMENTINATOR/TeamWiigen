using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using Sciifii.Downloader.Tools;
using System.Windows.Navigation;

namespace Sciifii.Downloader
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        void App_Navigated(object sender, NavigationEventArgs e)
        {
            int borderSize = 10;
            this.MainWindow.Height = (1.5 * 480) + borderSize;
            this.MainWindow.Width = (1.5 * 640) + borderSize;
            this.MainWindow.WindowStyle = WindowStyle.None;
            this.MainWindow.ResizeMode = ResizeMode.CanMinimize;
            Page page = e.Content as Page;
            if (page != null)
                ApplicationHelper.NavigationService = page.NavigationService;
        }
    }
}
