using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace SciifiiDTO
{
    public partial class sciifiiStepsCorpInstaller
    {
        public void Download(string folder, sciifii config, BackgroundWorker worker, int step, int nbStep)
        {
            double cstep = (double)step / nbStep;

            foreach (sciifiiCorpItem item in config.corp)
            {
                if (worker.CancellationPending)
                    break;

                worker.ReportProgress((int)(100 * cstep));

                NUSDownloader.DownloadWad(0x100000000UL + item.source, item.revision, folder);

                cstep += (double)1 / (config.corp.Length * nbStep);
            }

            worker.ReportProgress(100);
        }
    }
}
