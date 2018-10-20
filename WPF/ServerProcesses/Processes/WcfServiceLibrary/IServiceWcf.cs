using System.Collections.Generic;
using System.Runtime.Serialization;
using System.ServiceModel;

namespace WcfServiceLibrary
{
    [ServiceContract]
    public interface IServiceWcf
    {
        [OperationContract]
        void StartProcess(string procName);

        [OperationContract]
        void KillProcess(string procName);

        [OperationContract]
        List<ProcessProps> GetProcesses();
    } // IServiceWcf


    /// <summary>
    /// CompositeType
    /// </summary>
    [DataContract]
    public class ProcessProps
    {
        public ProcessProps() { }
        public ProcessProps(string processName, string basePriority, string id, string sessionId,
                            string threads, string peakWorkingSet64, string nonpagedSystemMemorySize64,
                            string pagedMemorySize64, string pagedSystemMemorySize64, string peakPagedMemorySize64,
                            string peakVirtualMemorySize64, string privateMemorySize64)
        {
            ProcessName = processName;
            BasePriority = basePriority;
            Id = id;
            SessionId = sessionId;
            Threads = threads;
            PeakWorkingSet64 = peakWorkingSet64;
            NonpagedSystemMemorySize64 = nonpagedSystemMemorySize64;
            PagedMemorySize64 = pagedMemorySize64;
            PagedSystemMemorySize64 = pagedSystemMemorySize64;
            PeakPagedMemorySize64 = peakPagedMemorySize64;
            PeakVirtualMemorySize64 = peakVirtualMemorySize64;
            PrivateMemorySize64 = privateMemorySize64;
        } // FileProps


        // Уникальный идентификатор
        [DataMember]
        public string Id { get; set; }

        // Имя процесса
        [DataMember]
        public string ProcessName { get; set; }

        // Идентификатор сеанса служб
        [DataMember]
        public string SessionId { get; set; }

        // Базовый приоритет
        [DataMember]
        public string BasePriority { get; set; }

        // Количество потоков 
        [DataMember]
        public string Threads { get; set; }

        // Максимальный объём физической памяти
        [DataMember]
        public string PeakWorkingSet64 { get; set; }

        // Объём невыгружаемой системой памяти
        [DataMember]
        public string NonpagedSystemMemorySize64 { get; set; }

        // Объём выгружаемой памяти
        [DataMember]
        public string PagedMemorySize64 { get; set; }

        // Объём выгружаемой системой памяти
        [DataMember]
        public string PagedSystemMemorySize64 { get; set; }

        // Максимальный объём памяти в файле подкачки виртуальной памяти
        [DataMember]
        public string PeakPagedMemorySize64 { get; set; }

        // Максимальный объём виртуальной памяти
        [DataMember]
        public string PeakVirtualMemorySize64 { get; set; }

        // Объём закрытой системой памяти
        [DataMember]
        public string PrivateMemorySize64 { get; set; }
    } // ProcessProps
} // WcfServiceLibrary