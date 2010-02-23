using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace SciifiiDTO
{
    public partial class sciifiiStepsIOSDowngrader
    {
        public void Download(string folder, sciifii config, BackgroundWorker worker, int step, int nbStep)
        {
            double progress = (double)step / nbStep;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(0x100000000UL + this.id, 0, folder);

            progress += 0.5 / nbStep;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(0x100000000UL + this.id, revision, folder);

            progress += 0.5 / nbStep;
            worker.ReportProgress((int)(100 * progress));
        }
    }
}
