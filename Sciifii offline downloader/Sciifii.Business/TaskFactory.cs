using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Sciifii.DTO;
using System.Globalization;
using Sciifii.DTO.Steps;
using Sciifii.DTO.Steps.Patches;

namespace Sciifii.Business
{
    public class TaskFactory
    {
        private string GetRealPath(string folder, string path)
        {
            string sdDirectory = path.Substring(path.IndexOf('/'));
            string device = path.Substring(0, path.IndexOf('/') - 1);


            string realDirectory = folder + "\\" + sdDirectory;
            realDirectory = realDirectory.Replace("/", "\\");

            while (realDirectory.Contains("\\\\"))
            {
                realDirectory = realDirectory.Replace("\\\\", "\\");
            }

            return realDirectory;
        }

        internal void PrepareCiosInstaller(BaseStep s, string folder, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            CiosInstaller step = s as CiosInstaller;
            double progressStep = 1.0 / ((String.IsNullOrEmpty(step.BannerSourceFile) ? 1 : 2) + step.Modules.Count);

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress));
            message("IOS" + step.IosVersion + " rev" + step.IosRevision + ": Downloading");

            NUSDownloader.DownloadWad(0x100000000UL + step.IosVersion, step.IosRevision, GetRealPath(folder, Configuration.Current.WorkingDirectory));
            message("IOS" + step.IosVersion + " rev" + step.IosRevision + ": Downloaded");

            progress += progressStep / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            foreach (Module module in step.Modules)
            {
                if (worker.CancellationPending)
                    break;

                File file = Configuration.Current.Files.Where(f => f.Key == module.SourceFile).FirstOrDefault();

                FileDownloader.Download(file.Key, file.Url, file.Sha1Url, file.Path, folder, Configuration.Current.WorkingDirectory);
                message(file.Key);

                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress));
            }

            if (!String.IsNullOrEmpty(step.BannerSourceFile))
            {
                File file = Configuration.Current.Files.Where(f => f.Key == step.BannerSourceFile).FirstOrDefault();
                FileDownloader.Download(file.Key, file.Url, file.Sha1Url, file.Path, folder, Configuration.Current.WorkingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress));
            }
        }

        internal void PrepareTitleInstaller(BaseStep s, string folder, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            Title step = s as Title;
            if (step.Action == TitleAction.Install || step.Action == TitleAction.PackAsWad || step.Action == TitleAction.Update) // steps which requires download
            {

                if (!String.IsNullOrEmpty(step.Id))
                {

                    NUSDownloader.DownloadWad(UInt64.Parse(step.Id, System.Globalization.NumberStyles.HexNumber), step.Revision, GetRealPath(folder, Configuration.Current.WorkingDirectory));
                    if (step.Revision != 0)
                        message("Title " + step.Id + " rev" + step.Revision);
                    else
                        message("Title " + step.Id);

                }
                else
                {
                    File file = Configuration.Current.Files.Where(mf => mf.Key == step.WadFile).First();
                    FileDownloader.Download(file.Key, file.Url, file.Sha1Url, file.Path, folder, Configuration.Current.WorkingDirectory);
                    message(file.Key);
                }
            }

                double progress = (double)(stepIndex + 1) / nbSteps;
                worker.ReportProgress((int)(100 * progress));
        }

        internal void PrepareFileDownloader(BaseStep s, string folder, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            String fileName = "";
            
            if(s is DTO.Steps.FileDownloader)
            {
                DTO.Steps.FileDownloader step = s as DTO.Steps.FileDownloader;
                fileName = step.File;
            }
            else
            {
                Preloader step = s as Preloader;
                fileName = step.File;
            }

            File file = Configuration.Current.Files.Where(mf => mf.Key == fileName).First();

            FileDownloader.Download(file.Key, file.Url, file.Sha1Url, file.Path, folder, Configuration.Current.WorkingDirectory);
            message(file.Key);

            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal void PrepareEmptyTask(BaseStep s, string folder, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal void PrepareComposite(BaseStep s, string folder, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs,int stepIndex, int nbSteps)
        {
            CompositeInstaller step = s as CompositeInstaller;
            foreach (BaseStep innerStep in step.Steps)
            {
                System.Threading.Thread.Sleep(1000);
                if (worker.CancellationPending)
                    break;

                if (!innerStep.Regions.Contains(Configuration.Current.SelectedRegion) & innerStep.Regions.Count != 0)
                    continue;

                Task t = CreateTask(innerStep);

                if (innerStep is CompositeInstaller)
                {
                    t.Prepare(folder, worker, workerArgs, stepIndex, nbSteps);
                    stepIndex += (innerStep as CompositeInstaller).StepsFullCount;
                }
                else
                    t.Prepare(folder, worker, workerArgs, stepIndex++, nbSteps);
            }

            if (worker.CancellationPending)
                workerArgs.Cancel = true;
        }

        public Task CreateTask(BaseStep step)
        {
            if (step is CiosInstaller)
                return new Task { Step = step, job = PrepareCiosInstaller };
            else if (step is Title)
                return new Task { Step = step, job = PrepareTitleInstaller };
            else if (step is DTO.Steps.FileDownloader)
                return new Task { Step = step, job = PrepareFileDownloader };
            else if (step is CompositeInstaller)
                return new Task { Step = step, job = PrepareComposite };
            else
                return new Task { Step = step, job = PrepareEmptyTask };
        }

        public event MessageEventHandler message;

        private void Log(string msg)
        {
            message(msg);
        }
    }

    public delegate void MessageEventHandler(String message);
}