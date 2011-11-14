using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Sciifii.DTO.Steps;

namespace Sciifii.Business
{
    public delegate void TaskDelegate(BaseStep step, string folder, BackgroundWorker worker, DoWorkEventArgs workerArgs, int stepIndex, int nbSteps);

    public class Task
    {
        internal TaskDelegate job { get; set; }

        internal BaseStep Step { get; set; }

        public void Prepare(string folder, BackgroundWorker worker, DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            job(Step, folder, worker, workerArgs, stepIndex, nbSteps);
        }
    }
}
