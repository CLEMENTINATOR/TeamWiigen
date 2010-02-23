using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace SciifiiDTO
{
    public partial class sciifiiStepsCiosInstaller
    {
        public void Download(string folder, sciifii config, BackgroundWorker worker, int step, int nbStep)
        {
            double progress = (double)step / nbStep;

            worker.ReportProgress((int)(100 * progress));
            NUSDownloader.DownloadWad(0x100000000UL + 38, 3867, folder);

            progress += (double)1 / nbStep;
            worker.ReportProgress((int)(100 * progress));
        }
    }
}
