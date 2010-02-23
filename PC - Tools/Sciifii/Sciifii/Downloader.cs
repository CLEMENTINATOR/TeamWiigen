using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.IO;
using System.Reflection;
using SciifiiDTO;

namespace Sciifii
{
    class Downloader
    {
        object[] steps;
        sciifii config;
        BackgroundWorker worker;
        string folder;

        public Downloader(object[] steps, string folder, sciifii config, BackgroundWorker worker)
        {
            this.steps = steps;
            this.worker = worker;
            this.folder = folder + "\\sciifii";
            this.config = config;
        }

        public void ExecuteDownload()
        {
            Directory.CreateDirectory(folder);
            int stepIndex = 0;
            foreach (Object o in steps)
            {
                if (worker.CancellationPending)
                    break;

                MethodInfo nfo = o.GetType().GetMethod("Download");
                if (nfo != null)
                    nfo.Invoke(o, new Object[] { folder, config, worker, stepIndex++, steps.Length });
            }
        }
    }
}
