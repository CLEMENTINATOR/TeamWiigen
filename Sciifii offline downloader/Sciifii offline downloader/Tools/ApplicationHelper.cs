using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Navigation;

namespace Sciifii.Downloader.Tools
{
    public static class ApplicationHelper
    {
        private static NavigationService navigator;

        public static NavigationService NavigationService
        {
            set { navigator = value; }
            get { return navigator; }
        }
    }
}
