using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace InsuranceAgency.Model
{
    class Client
    {
        public int Id { get; set; }
        public string SecondName { get; set; }
        public string FirstName { get; set; }
        public string MiddleName { get; set; }
        public string Passport { get; set; }
        public double Discount { get; set; }
        public BitmapImage Photo { get; set; }
    } // class Clients
}
