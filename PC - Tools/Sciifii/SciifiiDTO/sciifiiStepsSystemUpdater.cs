using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace SciifiiDTO
{
    public partial class sciifiiStepsSystemUpdater
    {
        public void Download(string folder, sciifii config, BackgroundWorker worker, int step, int nbStep)
        {
            double cstep = (double)step / nbStep;

            foreach (sciifiiTitle item in config.system)
            {
                if (worker.CancellationPending)
                    break;

                worker.ReportProgress((int)(100 * cstep));

                NUSDownloader.DownloadWad(UInt64.Parse(item.id, System.Globalization.NumberStyles.HexNumber), UInt16.Parse(item.revision, System.Globalization.NumberStyles.HexNumber), folder);

                cstep += (double)1 / (config.system.Length * nbStep);
            }

            worker.ReportProgress(100);
        }
    }
}
