using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Car_company
{
    public class DataBus
    {
        // Фамилия и инициалы водителя
        private string surname;
        public string Surname {
            get { return surname; }
            set { surname = value; }
        } // Surname


        // Гос.номер автобуса
        private string numbers;
        public string Numbers {
            get { return numbers; }
            set { numbers = value; }
        } // Numbers


        // Марка производителя
        private string manufacturer;
        public string Manufacturer {
            get { return manufacturer; }
            set { manufacturer = value; }
        } // Manufacturer


        // Год выпуска автобуса
        private int yearOfIssue;
        public int YearOfIssue {
            get { return yearOfIssue; }
            set { yearOfIssue = value; }
        } // YearOfIssue


        // Пробег автобуса
        private double mileage;
        public double Mileage {
            get { return mileage; }
            set { mileage = value; }
        } // Mileage

    } // class DataBus
} // namespace Car_company
