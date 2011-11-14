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
using System.Windows.Shapes;
using Sciifii.Downloader.ViewModel;

namespace Sciifii.Downloader.Views
{
    /// <summary>
    /// Interaction logic for Test.xaml
    /// </summary>
    public partial class MenuView : Page
    {
        public MenuView()
        {           
            InitializeComponent();

            controls = new List<Control>();
            MenuViewModel model = new MenuViewModel();
            model.PropertyChanged += MenuView_PropertyChanged;
            this.DataContext = model;
            ReloadItems();
        }       

        void MenuView_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "CurrentMenuItems")
                ReloadItems();
        }

        #region view
        List<Control> controls;
        int nbSkip;

        private void ReloadItems()
        {
            foreach (Control c in controls)
                dynamicMenu.Children.Remove(c);

            controls.Clear();

            foreach (DTO.Menus.MenuItem item in (DataContext as MenuViewModel).CurrentMenuItems)
            {
                Control c = new Control();
                
                string[] nameParts = item.GetType().Name.Split('.');

                c.Style = (Style)layout.FindResource(nameParts.Last());
                c.DataContext = item;
                c.Visibility = System.Windows.Visibility.Collapsed;

                dynamicMenu.Children.Add(c);
                controls.Add(c);
            }

            nbSkip = 0;
            btnUp.IsEnabled = false;
            EnsureVisual();
        }

        private void EnsureVisual()
        {
            double offsetX = 12;
            double offsetY = 48;
            int currentLine = 0;
            double maxHeight = 0;

            foreach (Control c in controls)
            {
                DTO.Menus.MenuItem item = c.DataContext as DTO.Menus.MenuItem;

                //detect when we need to put new lines
                if ((item.BreakBefore && offsetX != 12) || (offsetX + c.Width > dynamicMenu.Width - 12))
                {
                    offsetX = 12;
                    if (currentLine >= nbSkip)
                        offsetY += 3 + maxHeight;

                    currentLine++;
                    maxHeight = 0;
                }

                //getting the max height item of the line                
                if(maxHeight < c.Height)
                    maxHeight = c.Height;

                //setting the items position and visibility                
                if(currentLine < nbSkip)
                    c.Visibility = System.Windows.Visibility.Collapsed;
                else if(offsetY + c.Height + 48 > dynamicMenu.Height)
                {                        
                    btnDown.IsEnabled = true;
                    c.Visibility = System.Windows.Visibility.Collapsed;
                }
                else                
                {                        
                    c.Visibility = System.Windows.Visibility.Visible;
                    Canvas.SetLeft(c, offsetX);
                    Canvas.SetTop(c, offsetY);
                }
                
                //setting the Position for the next item                
                if(item.BreakAfter)
                {                        
                    offsetX = 12; 
                    offsetY += maxHeight + 3;
                    maxHeight = 0;                        
                    currentLine++;                
                }                
                else                        
                    offsetX += c.Width + 12;
            }
        }
        #endregion

        private void btnUp_Click(object sender, RoutedEventArgs e)
        {
            nbSkip--;
            btnUp.IsEnabled = (nbSkip != 0);
            btnDown.IsEnabled = false;
            EnsureVisual();
        }

        private void btnDown_Click(object sender, RoutedEventArgs e)
        {
            nbSkip++;
            btnUp.IsEnabled = true;
            btnDown.IsEnabled = false;
            EnsureVisual();
        }

        private void Thumb_DragDelta(object sender, System.Windows.Controls.Primitives.DragDeltaEventArgs e)
        {
            App.Current.MainWindow.Left += e.HorizontalChange;
            App.Current.MainWindow.Top += e.VerticalChange;
        }
    }
}
