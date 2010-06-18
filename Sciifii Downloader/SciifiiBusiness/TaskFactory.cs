using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SciifiiDTO;
using SciifiiDTO.Corp;
using SciifiiDTO.Cios;
using System.Globalization;
using SciifiiDTO.Updater;

namespace SciifiiBusiness
{
    public class TaskFactory
    {
        private static string GetRealPath(string folder, string path)
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

        internal static void PrepareCorp(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            CiosCorp step = s as CiosCorp;
            double progressStep = 1.0 / (1 + step.Items.Count + step.Modules.Count);

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress),"CiosCorp download started");

            foreach (CorpModule m in step.Modules)
            {
                if (worker.CancellationPending)
                    break;
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == m.File).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress),file.Key+" downloaded");
            }

            foreach (CorpItem i in step.Items)
            {
                if (worker.CancellationPending)
                    break;
                if (!i.LocalOnly)
                {
                    progress += progressStep / nbSteps;
                    NUSDownloader.DownloadWad(UInt64.Parse(i.Source, System.Globalization.NumberStyles.HexNumber), i.TitleRevision, GetRealPath(folder, config.workingDirectory));
                    worker.ReportProgress((int)(100 * progress), "IOS " + i.Source + " v" + i.TitleRevision + " downloaded");
                }
            }
        }

        internal static void PrepareCiosInstaller(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            CiosInstaller step = s as CiosInstaller;
            double progressStep = 1.0 / (1 + step.Modules.Count + step.Plugins.Count);

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress),"CiosInstaller download started");

            NUSDownloader.DownloadWad(0x100000000UL + step.Source, 0, GetRealPath(folder, config.workingDirectory));

            progress += progressStep / nbSteps;
            worker.ReportProgress((int)(100 * progress),"Base "+step.Source+" ios downloaded");

            foreach (CiosModule module in step.Modules)
            {
                if (worker.CancellationPending)
                    break;
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == module.File).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress),file.Key+" downloaded");
            }

            foreach (Plugin plug in step.Plugins)
            {
                if (worker.CancellationPending)
                    break;
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == plug.File).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress),file.Key + " downloaded");
            }
        }

        internal static void PrepareTitleInstaller(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            TitleInstaller step = s as TitleInstaller;
            string str;
            if (!String.IsNullOrEmpty(step.TitleId))
            {
                NUSDownloader.DownloadWad(UInt64.Parse(step.TitleId, System.Globalization.NumberStyles.HexNumber), step.TitleRevision, GetRealPath(folder, config.workingDirectory));
                 str="Title "+step.TitleId;
                if(step.TitleRevision!=0) str+=" v"+step.TitleRevision;
                str+=" downloaded";
            }
            else
            {
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == step.Wad).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                str=file.Key + " downloaded";
            }

            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress),str);
        }

        internal static void PrepareTitleDowngrader(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            TitleDowngrader step = s as TitleDowngrader;

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress),"TitleDowngraded download started");

            NUSDownloader.DownloadWad(UInt64.Parse(step.Id, NumberStyles.HexNumber), 0, GetRealPath(folder, config.workingDirectory));

            progress += 0.5 / nbSteps;
            worker.ReportProgress((int)(100 * progress), "IOS " + step.Id + " downloaded");

            NUSDownloader.DownloadWad(UInt64.Parse(step.Id, NumberStyles.HexNumber), step.Revision, GetRealPath(folder, config.workingDirectory));

            progress += 0.5 / nbSteps;
            worker.ReportProgress((int)(100 * progress), "IOS " + step.Id +" v"+step.Revision+ " downloaded");
        }

        internal static void PrepareSystemUpdate(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            SystemUpdater step = s as SystemUpdater;
            List<Title> titleToInstall = step.Titles.Where(t => t.Region == Regions.ALL || t.Region == config.SelectedRegion).ToList();
            double progressStep = 1.0 / titleToInstall.Count;

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress),"SystemUpdate download started !");

            foreach (Title t in titleToInstall)
            {
                if (worker.CancellationPending)
                    break;
                NUSDownloader.DownloadWad(UInt64.Parse(t.TitleId, System.Globalization.NumberStyles.HexNumber), t.TitleRevision, GetRealPath(folder, config.workingDirectory));
                progress += progressStep / nbSteps;
                string str = "Title " + t.TitleId;
                if (t.TitleRevision != 0) str += " v" + t.TitleRevision;
                str += " downloaded";
                worker.ReportProgress((int)(100 * progress),str);
            }
        }

        internal static void PrepareFileDownloader(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            SciifiiDTO.FileDownloader step = s as SciifiiDTO.FileDownloader;

            ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == step.FileKey).First();
            FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress),file.Key+" downloaded");
        }

        internal static void PrepareEmptyTask(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal static void PrepareComposite(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            CompositeInstaller step = s as CompositeInstaller;
            foreach (Step innerStep in step.Steps)
            {
                if (worker.CancellationPending)
                    break;
                Task t = CreateTask(innerStep);

                if (innerStep is CompositeInstaller)
                    t.Prepare(folder, config, worker, workerArgs, stepIndex, nbSteps);
                else
                    t.Prepare(folder, config, worker, workerArgs, stepIndex++, nbSteps);
            }

            if (worker.CancellationPending)
                workerArgs.Cancel = true;
        }

        internal static void PreparePreloader(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, System.ComponentModel.DoWorkEventArgs workerArgs, int stepIndex, int nbSteps)
        {
            Preloader step = s as Preloader;
            ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == step.File).First();
            FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress), file.Key + " downloaded");

        }

        public static Task CreateTask(Step step)
        {
            if (step is CiosCorp)
                return new Task { Step = step, job = PrepareCorp };
            else if (step is CiosInstaller)
                return new Task { Step = step, job = PrepareCiosInstaller };
            else if (step is TitleInstaller)
                return new Task { Step = step, job = PrepareTitleInstaller };
            else if (step is TitleDowngrader)
                return new Task { Step = step, job = PrepareTitleDowngrader };
            else if (step is SystemUpdater)
                return new Task { Step = step, job = PrepareSystemUpdate };
            else if (step is SciifiiDTO.FileDownloader)
                return new Task { Step = step, job = PrepareFileDownloader };
            else if (step is CompositeInstaller)
                return new Task { Step = step, job = PrepareComposite };
            else if (step is Preloader)
                return new Task { Step = step, job = PreparePreloader };
            else
                return new Task { Step = step, job = PrepareEmptyTask };
        }
    }
}
