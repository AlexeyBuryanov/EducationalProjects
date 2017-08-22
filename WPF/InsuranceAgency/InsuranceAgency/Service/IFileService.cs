using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InsuranceAgency
{
    public interface IFileService
    {
        List<object> Open(string filename);                    // загрузить коллекцию из файла
        void Save(string filename, List<object> planesList);   // сохранить коллекцию в файле
    } // IFileService
}
