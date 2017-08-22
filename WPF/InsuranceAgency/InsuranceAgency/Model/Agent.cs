using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace InsuranceAgency.Model
{
    class Agent
    {
        public int Id { get; set; }
        public string SecondName { get; set; }
        public string FirstName { get; set; }
        public string MiddleName { get; set; }
        public double Reward { get; set; }
        public BitmapImage Photo { get; set; }
    } // class Agent
}
