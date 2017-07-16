using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Car_sale
{
    [Serializable]
    public class Car
    {
        // Производитель
        private string manufacturer;
        public string Manufacturer {
            get { return manufacturer; }
            set { manufacturer = value; }
        } // Manufacturer


        // Категория транспорта
        private string transportCategory;
        public string TransportCategory {
            get { return transportCategory; }
            set { transportCategory = value; }
        } // TransportCategory


        // Вид оплаты
        private string typePayment;
        public string TypePayment {
            get { return typePayment; }
            set { typePayment = value; }
        } // TypePayment


        // Дополнительное оборудование
        private Optional optional;
        public Optional Optional {
            get { return optional; }
            set { optional = value; }
        } // Optional
    } // class Car
}
