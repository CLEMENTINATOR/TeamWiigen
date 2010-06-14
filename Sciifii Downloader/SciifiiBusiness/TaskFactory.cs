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
        internal static void PrepareCorp(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            CiosCorp step = s as CiosCorp;
            double progressStep = 1.0 / (1 + step.Items.Count + step.Modules.Count);

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            foreach (CorpModule m in step.Modules)
            {
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == m.File).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress));
            }

            foreach (CorpItem i in step.Items)
            {
                NUSDownloader.DownloadWad(UInt64.Parse(i.Source, System.Globalization.NumberStyles.HexNumber), i.TitleRevision, folder);
            }
        }

        internal static void PrepareCiosInstaller(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            CiosInstaller step = s as CiosInstaller;
            double progressStep = 1.0 / (1 + step.Modules.Count + step.Plugins.Count);

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(0x100000000UL + step.Source, 0, folder);

            progress += progressStep / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            foreach (CiosModule module in step.Modules)
            {
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == module.File).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress));
            }

            foreach (Plugin plug in step.Plugins)
            {
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == plug.File).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress));
            }
        }

        internal static void PrepareTitleInstaller(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            TitleInstaller step = s as TitleInstaller;
            if (!String.IsNullOrEmpty(step.TitleId))
                NUSDownloader.DownloadWad(UInt64.Parse(step.TitleId, System.Globalization.NumberStyles.HexNumber), step.TitleRevision, folder);
            else
            {
                ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == step.Wad).First();
                FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
            }

            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal static void PrepareTitleDowngrader(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            TitleDowngrader step = s as TitleDowngrader;

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(UInt64.Parse(step.Id, NumberStyles.HexNumber), 0, folder);

            progress += 0.5 / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            NUSDownloader.DownloadWad(UInt64.Parse(step.Id, NumberStyles.HexNumber), step.Revision, folder);

            progress += 0.5 / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal static void PrepareSystemUpdate(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            SystemUpdater step = s as SystemUpdater;
            List<Title> titleToInstall = step.Titles.Where(t => t.Region == Regions.ALL || t.Region == config.SelectedRegion).ToList();
            double progressStep = 1.0 / titleToInstall.Count;

            double progress = (double)stepIndex / nbSteps;
            worker.ReportProgress((int)(100 * progress));

            foreach (Title t in titleToInstall)
            {
                NUSDownloader.DownloadWad(UInt64.Parse(t.TitleId, System.Globalization.NumberStyles.HexNumber), t.TitleRevision, folder);
                progress += progressStep / nbSteps;
                worker.ReportProgress((int)(100 * progress));
            }
        }

        internal static void PrepareFileDownloader(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            SciifiiDTO.FileDownloader step = s as SciifiiDTO.FileDownloader;

            ManagedFile file = config.ManagedFiles.Where(mf => mf.Key == step.FileKey).First();
            FileDownloader.Download(file.Key, file.Url, file.ShaUrl, file.FilePath, folder, config.workingDirectory);
            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal static void PrepareEmptyTask(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            double progress = (double)(stepIndex + 1) / nbSteps;
            worker.ReportProgress((int)(100 * progress));
        }

        internal static void PrepareComposite(Step s, string folder, SciifiiConfiguration config, System.ComponentModel.BackgroundWorker worker, int stepIndex, int nbSteps)
        {
            CompositeInstaller step = s as CompositeInstaller;
            foreach (Step innerStep in step.Steps)
            {
                Task t = CreateTask(innerStep);

                if (innerStep is CompositeInstaller)
                    t.Prepare(folder, config, worker, stepIndex, nbSteps);
                else
                    t.Prepare(folder, config, worker, stepIndex++, nbSteps);
            }
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
            else
                return new Task { Step = step, job = PrepareEmptyTask };
        }
    }
}
