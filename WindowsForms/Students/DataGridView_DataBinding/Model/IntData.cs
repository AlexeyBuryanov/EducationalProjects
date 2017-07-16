using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataGridView_DataBinding
{
    // Вспомогательный класс для заполнения комбо-бокса в DataGridView
    // Необходим для реализации механизма привязки числовых данных к нечисловому 
    // элементу - комбобоксу
    public class IntData
    {
        // Хранение числовой составляющей
        private int intValue;
        public int IntValue {
            get { return intValue; }
            set { intValue = value; }
        } // IntValue

        // Хранение строковог образа числовой составляющей
        public string StrValue {
            get { return intValue == 0?" ":$"{intValue}"; }
            set { int.TryParse(value, out intValue); }
        } // StrValue

        // Ансамбль конструкторов
        public IntData() : this(0) { } // IntData
        public IntData(int val) { intValue = val; } // IntData
    } // class IntData
}
