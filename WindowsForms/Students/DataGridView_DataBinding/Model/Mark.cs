using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataGridView_DataBinding
{
    // Описание оценки
    public class Mark
    {
        // Название предмета
        private string subject;
        public string Subject {
            get { return subject; }
            set { subject = value; }
        } // Subject

        // Оценка по предмету
        private int level;
        public int Level {
            get { return level; }
            set { level = value; }
        } // Level

    } // class Mark
} // namespace DataGridView_DataBinding