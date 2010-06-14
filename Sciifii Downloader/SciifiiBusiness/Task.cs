using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SciifiiDTO;

namespace SciifiiBusiness
{
    public delegate void TaskDelegate(Step step, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps);

    public class Task
    {
        internal TaskDelegate job { get; set; }

        internal Step Step { get; set; }

        public void Prepare(string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            job(Step, folder, config, worker, stepIndex, nbSteps);
        }
    }
}
