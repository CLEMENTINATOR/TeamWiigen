using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace SciifiiDTO
{
    public partial class sciifiiStepsTruchaRestorer
    {
        public void Download(string folder, sciifii config, BackgroundWorker worker, int step, int nbStep)
        {
            double progress = (double)step / nbStep;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(0x100000000UL + this.id, this.revision, folder);

            progress += 1 / nbStep;
            worker.ReportProgress((int)(100 * progress));
        }
    }
}
