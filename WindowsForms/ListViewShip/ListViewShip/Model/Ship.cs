using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ListViewShip
{
    // необходим, т.к. выполняется сериализация объекта класса,
    // вкоючающего в себя класс Ship
    [Serializable]  
    public class Ship
    {
        // Имя файла - заместителя, при отсутствии фото корабля
        public static readonly string fileNoPhoto = "NoImage.png";

        // Идентификатор для корабля. Обеспечит уникальность записи
        private int id;   
        public int Id {
            get { return id; }
            set { if (value > 0) id = value; }
        } // Id

        // Название корабля
        private string name;
        public string Name {
            get { return name; }
            set { name = value; }
        } // Name

        // Водоизмещение
        private int displacement;
        public int Displacement {
            get { return displacement; }
            set { displacement = value; }
        } // Displacement

        // Максимальная скорость
        private double speed;
        public double Speed {
            get { return speed; }
            set { speed = value; }
        } // Speed

        // Дальность плавания
        private int cruisingRange;
        public int CruisingRange {
            get { return cruisingRange; }
            set { cruisingRange = value; }
        } // CruisingRange

        // Ссылка на файл изображения корабля
        private string filePhoto;
        public string FilePhoto {
            get { return filePhoto; }
            set { filePhoto = value; }
        } // FilePhoto


        // Ансамбль конструкторов
        public Ship(): this(1, "", 1, 1d, 1, fileNoPhoto) {}
        public Ship(int id, string name, int displacement, double speed, int cruisingRange, string filePhoto)
        {
            Id = id;
            Name = name;
            Displacement = displacement;
            Speed = speed;
            CruisingRange = cruisingRange;
            FilePhoto = filePhoto;
        } // Ship

    } // class Ship
}
