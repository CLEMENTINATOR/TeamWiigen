using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using Sciifii.DTO;

namespace Sciifii.Downloader.Tools
{
    [ValueConversion(typeof(string), typeof(bool))]
    public class SwitchConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            string key = value as string;
            Switch s = Configuration.Current.Switches.FirstOrDefault(sw => sw.Key == key);

            if (s == null)
            {
                s = new Switch { Key = key, Active = false };
                Configuration.Current.Switches.Add(s);
            }

            return s.Active;
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
