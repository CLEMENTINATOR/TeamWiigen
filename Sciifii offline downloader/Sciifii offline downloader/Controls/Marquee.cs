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
using System.Windows.Media.Animation;

namespace Sciifii.Downloader.Controls
{
    public class Marquee : ContentControl
    {
        #region Fields

        FrameworkElement container;
        FrameworkElement presenter;
        DoubleAnimationUsingKeyFrames animation;

        #endregion

        #region Ctors...

        static Marquee()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(Marquee), new FrameworkPropertyMetadata(typeof(Marquee)));
        }

        public Marquee()
        {
            animation = new DoubleAnimationUsingKeyFrames();
            Loaded += new RoutedEventHandler(Marquee_Loaded);
        }

        void Marquee_Loaded(object sender, RoutedEventArgs e)
        {
            StartMarquee();

            if (container != null)
                container.SizeChanged += (s, args) => { StartMarquee(); };

            if (presenter != null)
                presenter.SizeChanged += (s, args) => { StartMarquee(); };
        }

        #endregion

        #region Event Handlers

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            container = Template.FindName("PART_Container", this) as FrameworkElement;
            presenter = Template.FindName("PART_Presenter", this) as FrameworkElement;
        }

        #endregion

        private void StartMarquee()
        {
            double margin = 5;

            presenter.BeginAnimation(Canvas.LeftProperty, null);

            Canvas.SetTop(presenter, (container.ActualHeight - presenter.ActualHeight) / 2);
            if (container.ActualWidth - presenter.ActualWidth - margin >= 0)
            {
                Canvas.SetLeft(presenter, (container.ActualWidth - presenter.ActualWidth) / 2);
                return;
            }

            animation.Duration = new Duration(TimeSpan.FromSeconds(4));
            animation.KeyFrames.Add(new LinearDoubleKeyFrame(margin, KeyTime.FromTimeSpan(TimeSpan.FromSeconds(0))));
            animation.KeyFrames.Add(new LinearDoubleKeyFrame(margin, KeyTime.FromTimeSpan(TimeSpan.FromSeconds(1))));
            animation.KeyFrames.Add(new LinearDoubleKeyFrame(container.ActualWidth - presenter.ActualWidth - margin, KeyTime.FromTimeSpan(TimeSpan.FromSeconds(3))));
            animation.KeyFrames.Add(new LinearDoubleKeyFrame(container.ActualWidth - presenter.ActualWidth - margin, KeyTime.FromTimeSpan(TimeSpan.FromSeconds(4))));
            animation.AutoReverse = true;
            animation.RepeatBehavior = RepeatBehavior.Forever;
            presenter.BeginAnimation(Canvas.LeftProperty, animation);
        }
    }
}
