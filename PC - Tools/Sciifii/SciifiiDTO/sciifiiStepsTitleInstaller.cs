using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace SciifiiDTO
{
    public partial class sciifiiStepsTitleInstaller
    {
        public void Download(string folder, sciifii config, BackgroundWorker worker, int step, int nbStep)
        {
            double progress = (double)step / nbStep;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(UInt64.Parse(this.id, System.Globalization.NumberStyles.HexNumber), UInt16.Parse(this.revision, System.Globalization.NumberStyles.HexNumber), folder);

            progress += 1 / nbStep;
            worker.ReportProgress((int)(100 * progress));
        }
    }
}
