using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataGridView_DataBinding
{
    public class Student
    {
        // Идентификационный номер студента
        private int id;
        public int Id {
            get { return id; }
            set { id = value; }
        } // Id


        // Фамилия и инициалы
        private string surname;
        public string Surname {
            get { return surname; }
            set { surname = value; }
        } // Surname


        // Пол
        private string gender;
        public string Gender {
            get { return gender; }
            set { gender = value; }
        } // Gender


        // Дата рождения
        private DateTime birthDate;
        public DateTime BirthDate {
            get { return birthDate; }
            set { birthDate = value; }
        } // BirthDate


        // Курс обучения
        private int course;
        public int Course {
            get { return course; }
            set { course = value; }
        } // Course


        // Название группы 
        private string group;
        public string Group {
            get { return group; }
            set { group = value; }
        } // Group


        // Получает ли стипендию (true)
        private bool scholarship;
        public bool Scholarship {
            get { return scholarship; }
            set { scholarship = value; }
        } // Scholarship


        // Список оценок студента
        private List<Mark> marks;
        public List<Mark> Marks {
            get { return marks; }
            set { marks = value; }
        } // Marks


        // Вычисляемое свойство для вычисляемого столбца - средний балл
        // студента по проставленным оценкам. Если оценок нет, то
        // средний балл == 0
        public double AvgLevel {
            get {
                // Нет оценок - средний балл равен нулю
                if (Marks == null) return 0d;

                // LINQ-запрос (Language INtegrated Queries - язык интегрированных запросов)
                // изучать будм позже, применять будем позже  
                // return Marks.Where(x => x.Level != 0d).Average(x => x.Level);

                // Пока делаем по старинке... расчет среднего арфиметчиеского
                // по выставленным оценкам
                int markCounter = 0;   // счетчик выставленных оценок
                double markAvg = 0d;   // сумма оценок и среднее арифметическое оценок
                foreach (var item in Marks) {    // Для каждого элемента списка оценок
                    if (item.Level != 0d) {      // подсчет суммы и количества выставленных оценок
                        markCounter++;
                        markAvg += item.Level;
                    } // if
                } // foreach

                // Если есть оценки, вернем среднее арифметическое (средний балл)
                // Если нет оценок - вернем 0d
                if (markCounter != 0) markAvg /= markCounter;
                return markAvg;
            } // get
        } // AvgLevel
    } // class Student
}
