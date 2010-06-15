using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.IO;
using System.Reflection;
using SciifiiDTO;
using SciifiiBusiness;

namespace Sciifii
{
    class Downloader
    {
        DoWorkEventArgs workerArgs;
        SciifiiConfiguration config;
        BackgroundWorker worker;
        string folder;

        public Downloader(DoWorkEventArgs workerArgs, string folder, SciifiiConfiguration config, BackgroundWorker worker)
        {
            this.workerArgs = workerArgs;
            this.worker = worker;
            this.folder = folder;
            this.config = config;
        }

        public void ExecuteDownload()
        {
            Directory.CreateDirectory(folder);
            CompositeInstaller container = new CompositeInstaller();
            
            foreach (Step s in (IEnumerable<Step>)workerArgs.Argument)
                container.Steps.Add(s);

            TaskFactory.CreateTask(container).Prepare(folder, config, worker, workerArgs, 0, container.StepsFullCount);
        }
    }
}
