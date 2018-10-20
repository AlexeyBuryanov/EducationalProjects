using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace WcfServiceLibrary
{
    public class ServiceWcf : IServiceWcf
    {
        /// <summary>
        /// Запускает ресурс процесса путём указания имени файла приложения
        /// </summary>
        /// <param name="procName">Имя файла приложения</param>
        public void StartProcess(string procName)
        {
            Process.Start(procName);
        } // StartProcess


        /// <summary>
        /// Немедленно останавливает процесс
        /// </summary>
        /// <param name="procName">Имя файла приложения</param>
        public void KillProcess(string procName)
        {
            Process.GetProcessesByName(procName)
                .ToList()
                .ForEach(process => {
                process.Kill();
            });
        } // KillProcess


        /// <summary>
        /// Возвращает список процессов выполняющихся на сервере
        /// </summary>
        /// <returns>
        /// Список процессов в виде типа ProcessProps, который хранит 
        /// в себе все необходимые свойства
        /// </returns>
        public List<ProcessProps> GetProcesses()
        {
            var list = new List<ProcessProps>();
            Process.GetProcesses()
                .ToList()
                .ForEach(process => {
                list.Add(new ProcessProps(process.ProcessName, process.BasePriority.ToString(), process.Id.ToString(), 
                    process.SessionId.ToString(), process.Threads.Count.ToString(), (process.PeakWorkingSet64/1024/1024).ToString()+" Мб", 
                    (process.NonpagedSystemMemorySize64/1024/1024).ToString()+" Мб", (process.PagedMemorySize64/1024/1024).ToString()+" Мб",
                    (process.PagedSystemMemorySize64/1024/1024).ToString()+" Мб", (process.PeakPagedMemorySize64/1024/1024).ToString()+" Мб",
                    (process.PeakVirtualMemorySize64/1024/1024).ToString()+" Мб", (process.PrivateMemorySize64/1024/1024).ToString()+" Мб"));
            });
            return list;
        } // GetProcesses
    } // ServiceWcf
} // WcfServiceLibrary