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
        IEnumerable<Step> steps;
        SciifiiConfiguration config;
        BackgroundWorker worker;
        string folder;

        public Downloader(IEnumerable<Step> steps, string folder, SciifiiConfiguration config, BackgroundWorker worker)
        {
            this.steps = steps;
            this.worker = worker;
            this.folder = folder + "\\sciifii";
            this.config = config;
        }

        public void ExecuteDownload()
        {
            Directory.CreateDirectory(folder);
            CompositeInstaller container = new CompositeInstaller();
            
            foreach (Step s in steps)
                container.Steps.Add(s);

            TaskFactory.CreateTask(container).Prepare(folder, config, worker, 0, container.StepsFullCount);
        }
    }
}
