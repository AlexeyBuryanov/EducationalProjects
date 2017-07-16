using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TableFunctions
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        } // MainForm


        // Заполнить таблицу при загрузке формы
        private void MainForm_Load(object sender, EventArgs e)
        {
            int n = 100;  // количество точек, выводимых в таблицу
            double step = 2*Math.PI / (n - 1);   // шаг вывода точек таблицы
            double x, sx, cx, tg, ctg;    // переменные для расчета таблицы

            // программное создание столбца, доступ для настройки параметров
            // первый параметр - имя столбца
            // второй параметр - загоовок столбца
            // Есть перегруженный вариант - создание из другого столбца
            // dgvTable.Columns.Add("None", "Примечание");   // создание
            // dgvTable.Columns["None"].FillWeight = 30;     // доступ через индексатор к свойствам

            dgvTable.RowCount = n;        // создать таблицу заданного размера

            x = -Math.PI;
            for (int i = 0; i < n; i++) {
                // Расчет очередной строки таблицы
                sx = Math.Sin(Math.PI + x);
                cx = Math.Cos(Math.PI + x);
                tg = Math.Tan(Math.PI + x);

                // Особый случай - обработка деления на ноль 
                ctg = Math.Abs(x - Math.PI) < 0.000001?double.PositiveInfinity:(cx / sx);

                // Заполнение очередной строки таблицы DataGridView
                // ‼ В индексаторе таблицы на первом месте - индекс столбца
                // ‼ на втором месте - индекс строки
                dgvTable[0, i].Value = $"{x,   8:f5}";
                dgvTable[1, i].Value = $"{sx,  8:f5}";
                dgvTable[2, i].Value = $"{cx,  8:f5}";
                dgvTable[3, i].Value = $"{tg,  8:f5}";
                dgvTable[4, i].Value = $"{ctg, 8:f5}";

                x += step;     // К следующей строке таблицы, к следующей точке расета 
            } // for i
        } // MainForm_Load

        // Выход из приложения
        private void mniExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        } // mniExit_Click
    }
}
