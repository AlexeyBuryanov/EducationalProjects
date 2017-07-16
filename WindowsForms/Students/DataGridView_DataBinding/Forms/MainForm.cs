using System;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace DataGridView_DataBinding
{
    public partial class MainForm : Form
    {
        // private List<Student> students;  // имя набора данных в памяти
        private XmlSerializer xmls;      // XML-сериализатор
        private string fileName;         // имя файла с набором данных

        const string EXTENTION    = "students",    // расширение для файлa набора данных
                     DEFAULT_NAME = "Безымянный";  // имя файла по умолчанию

        // заголовок окна, общая часть заголовка. Полный заголовок это:
        // общая часть и имя обрабатываемого файла
        const string DEFAULT_TEXT = "Данные о студентах";

        static readonly string[] InfoText = {
            "Файл",
            "Новый", "Загрузить...", "Сохранить...", "Выход",
            "Справка",
            "Информация о программе"
        };

        string goodEx = @"..\..\Icons\goodExclamation.png",
               badEx  = @"..\..\Icons\badExclamation.png";

        AboutForm aboutForm;

        public MainForm()
        {
            InitializeComponent();

            // students = new List<Student>();     // набор данных
            bnsDataGrid.DataSource = new List<Student>();  // привязка набора к таблице во время исполнения приложения
            // !!! Привязка к типу (объекту класса Students на время разработки дала возможность
            // настройки таблицы. Привязка к набору данных во время исполнения дает возможность
            // менять данные в наборе и автоматически менять их отображение в таблице и, наоборот,
            // меняя данные в таблице мы меняем их в наборе данных

            // Привязка оценок к подчиненной таблице
            bnsMarks.DataSource = bnsDataGrid;
            bnsMarks.DataMember = "Marks";

            // Привязка поля Text метки lblSurname к свойству Surname класса Student
            lblSurname.DataBindings.Add("Text", bnsDataGrid, "Surname");

            // Создать XML сериализатор - для сохранения данных из коллекции в XML-формате
            xmls = new XmlSerializer(typeof(List<Student>));

            // Имя файла с набором данных - по умолчанию "Безымянный";
            fileName = DEFAULT_NAME + "." + EXTENTION;
            Text = DEFAULT_TEXT + " - " + fileName;

            // Загрузка данных в столбцы с числовой информацией для выбора 
            // выпадающими списками
            SetIntData(1, 5, dgvMain.Columns["dgcCourse"]);
            SetIntData(1, 12, dgvMarks.Columns["dgcLevel"]);
            statusBar.Text = "Добро пожаловать";
        } // MainForm


        // Выход из приложения 
        private void mniExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        } // mniExit_Click


        // Проверка данных на уровне строки
        private void dgvMain_RowValidating(object sender, DataGridViewCellCancelEventArgs e)
        {
            // Если это последняя строка - не проверять ее, молча уходить
            if (dgvMain.Rows[e.RowIndex].IsNewRow) return;

            // Для остальных строк проверяем заполнение поля Фамилия И.О.
            string errMsg = "";
            if (dgvMain[1, e.RowIndex].Value == null) {
                errMsg = @"Поле ""Фамилия И.О."" должно быть заполнено";
            } // if

            // Вывести или стереть сообщение об ошибке
            dgvMain.Rows[e.RowIndex].ErrorText = errMsg;

            if (errMsg != "") {
                statusBar2.Visible   = true;
                statusBar2.ForeColor = System.Drawing.Color.Red;
                statusBar2.Image = System.Drawing.Image.FromFile(badEx);
                statusBar2.Text  = errMsg;
            } else statusBar2.Visible = false;

            // Оставить пользователя в строке или уйти из строки 
            e.Cancel = errMsg != "";
        } // dgvMain_RowValidating


        // Обработка ошибок на уровне ячейки - для каждой ячейки отдельный вызов
        private void dgvMain_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            // Если это последняя строка - не проверять ее, молча уходить
            if (dgvMain.Rows[e.RowIndex].IsNewRow) return;

            string s = e.FormattedValue.ToString();  // значение, прочитанное из ячейки
            string errMsg = "";                      // предполагаем, что ошибок нет
            string header = dgvMain.Columns[e.ColumnIndex].HeaderText + ": ";

            // Проверяем ошибки по столбцам - для каждого столбца система выполняет отдельный
            // выхов этого метода проверки 
            switch (e.ColumnIndex) {
                case 4:   // Курс - диапазон не контролируем, он задается выпадающим списоком
                    if (s == "" || s == "0") {
                        errMsg = header + "Поле должно быть заполнено";
                    } // if
                    break;

                case 2:   // Пол
                case 5:   // Группа
                    if (s == "") {
                        errMsg = header + "Поле должно быть заполнено";
                    } // if
                    break;

                case 3:   // Дата рождения
                    if (s == "") {
                        errMsg = header + "Поле должно быть заполнено";
                        break;
                    } // if

                    DateTime dt;
                    if (DateTime.TryParse(s, out dt)) {
                        // Прошло преобразование в дату, проверим возраст
                        int age = DateTime.Today.Year - dt.Year;
                        if (age < 15 || age > 55) {
                            errMsg = header + "Возраст студента должен быть в диапазоне от 15 до 55 лет";
                        } // if
                    } else {
                        errMsg = header + "Ожидается ввод даты в формате дд/мм/гггг";
                    } // if
                    break;
            } // switch

            // Вывести или стереть сообщение об ошибке
            dgvMain.Rows[e.RowIndex].ErrorText = errMsg;

            if (errMsg == "") {
                statusBar.Text = "Готово";
            } else if (errMsg != "") { // если есть ошибки
                statusBar.Text = "Ошибка";
                mniSave.Enabled = false;
                tsbSave.Enabled = false;

                statusBar2.Visible   = true;
                statusBar2.ForeColor = System.Drawing.Color.Red;
                statusBar2.Image = System.Drawing.Image.FromFile(badEx);
                statusBar2.Text  = errMsg;
            } else { statusBar2.Visible = false; }

            // Оставить пользователя в строке или уйти из строки 
            e.Cancel = errMsg != "";
        } // dgvMain_CellValidating


        // Сохранить текущие данные в  файле
        private void mniSave_Click(object sender, EventArgs e)
        {
            // Защита от записи пустого набора данных
            // Т.е. не записывать данные в файл, если в таблице только одна строка
            // (управляющая строка для ввода новой записи) 
            if (dgvMain.RowCount == 1) {
                statusBar2.Visible = true;
                statusBar2.ForeColor = System.Drawing.Color.Red;
                statusBar2.Image = System.Drawing.Image.FromFile(badEx);
                statusBar2.Text  = "Нельзя записать пустой набор данных";
                statusBar.Text   = "Ошибка";
                return;
            } // if

            // Если имя файла не задано, то запросить имя файла для редактирования
            if (fileName == DEFAULT_NAME + "." + EXTENTION) {
                if (sfdStudents.ShowDialog() != DialogResult.OK)
                    return;
                else {
                    fileName = sfdStudents.FileName;
                    Text = DEFAULT_TEXT + " - " + Path.GetFileName(fileName);
                } // if 
            } // if

            SaveData();
            ShowOKstatusBar2("сохранены");
        } // mniSave_Click


        // Загрузка файла данных
        private void mniLoad_Click(object sender, EventArgs e)
        {
            // Сохранение данных (если есть, что сохранять)
            if (dgvMain.RowCount > 1) SaveData();

            // Если не выбрано имя файла для сохранения, то молча выходим
            if (ofdStudents.ShowDialog() != DialogResult.OK) return;

            fileName = ofdStudents.FileName;
            Text = DEFAULT_TEXT + " - " + Path.GetFileName(fileName);
            LoadData();

            ShowOKstatusBar2("загружены");
            mniSave.Enabled = true;
            tsbSave.Enabled = true;
        } // mniLoad_Click


        // Сообщение об успехе сохранения или загрузки - в строке состояния, в ее 2-й половине
        private void ShowOKstatusBar2(string msg)
        {
            statusBar2.Visible = true;
            statusBar2.ForeColor = System.Drawing.Color.DarkGreen;
            statusBar2.Image = System.Drawing.Image.FromFile(goodEx);
            statusBar2.Text = $"Данные успешно {msg}";
            statusBar.Text = "Готово";
        } // ShowOKstatusBar2


        // Сохранение данных в XML-файле
        private void SaveData() {
            // Перред записью выполняется обмен между DGV и нашими данными
            // Если текущая строка DGV последняя, то некорректные данные
            // (пустая строка) пишутся в файл
            // Для исправления - делаем текущей строкой последнюю заполненную строку
            // RowCount-2 --> это и есть последняя заполненнся строка
            if (dgvMain.CurrentRow.IsNewRow) dgvMain.CurrentCell = dgvMain[0, dgvMain.RowCount - 2];

            using (StreamWriter sw = new StreamWriter(fileName, false, Encoding.Default)) {
                xmls.Serialize(sw, bnsDataGrid.DataSource);
            } // using
        } // SaveData


        // Загрузка данных из XML-файла
        private void LoadData()
        {
            // Для отображения загружаемых данных надо отключить привязку перед загрузкой
            // и включить привязку к данным после загрузки из файла данных
            bnsDataGrid.SuspendBinding();   // приостановить привязку
            using (StreamReader sr = new StreamReader(fileName, Encoding.Default)) {
                bnsDataGrid.DataSource = xmls.Deserialize(sr);
            } // using
            bnsDataGrid.ResumeBinding(); // возвобновить привязку к изменившемуся источнику данных
        } // LoadData


        // Сохраняем данные при закрытии формы - вызов штатного обработчика
        // команды сохранения
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            #region Имитация анимации в статус-баре по выходу
            statusBar2.Image = System.Drawing.Image.FromFile(goodEx);
            statusBar2.ForeColor = System.Drawing.Color.DarkGreen;
            statusBar2.Text = "Выход";

            for (int msWait = 500; msWait >= 200; msWait -= 100) {
                statusBar2.Text += " . .";
                Application.DoEvents();
                Thread.Sleep(msWait);
            } // for i
            Thread.Sleep(500); // эффект притормаживания...
            #endregion

            // TODO: Запрет завершения работы до окончания редактирования данных
            //       Это важно при выходе по команде меню. Если выход по кнопке X в окне 
            //       то режим редактирования завершается автоматически 
            //       Некорректные данные пропукаются :( 
            if (dgvMain.IsCurrentCellDirty) { 
                e.Cancel = true;
                return;
            } // if
            mniSave_Click(sender, EventArgs.Empty);
        } // MainForm_FormClosing


        // Событие срабатывает, если есть ячейка в режиме редактирования
        // и ячейка изменена, но Enter для закрепления изменений еще не был нажат
        // В таком случае запрещаем и загрузку и сохранения до закрепления измененных
        // данных - до нажатия на Enter
        private void dgvMain_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            // Пока есть ячейка в режиме редактирования - не сохранять данные
            mniNew.Enabled = mniLoad.Enabled = mniSave.Enabled =
                tsbSave.Enabled = tsbNew.Enabled = tsbLoad.Enabled =
                !dgvMain.IsCurrentCellDirty;

            // реализация автоинкремента поля идентификатора 
            // еслти в текущей строке поле идентиффкатора == 0, то найти максимальный
            // идентификатор в списке и, увеличив его на 1, записать в grid (т.е.
            // в коллекцию данных)
            int row = dgvMain.CurrentRow.Index;
            if ((int)dgvMain["dgcId", row].Value == 0) {
                dgvMain["dgcId", row].Value = GetMaxId() + 1;
            } // if
        } // dgvMain_CurrentCellDirtyStateChanged


        // Возвращает максимальный идентификатор из списка студентов
        private int GetMaxId()
        {
            List<Student> students = bnsDataGrid.DataSource as List<Student>;

            int maxId = students[0].Id;
            for (int i = 1; i < students.Count(); i++)
                if (students[i].Id > maxId) maxId = students[i].Id;
            return maxId;
        } // GetMaxId


        // Новый
        private void new_Click(object sender, EventArgs e)
        {
            bnsDataGrid.SuspendBinding();                 // отключаем привязку данных
            bnsDataGrid.DataSource = new List<Student>(); // новый список
            bnsDataGrid.ResumeBinding();                  // переподключаем данные
            fileName = DEFAULT_NAME + "." + EXTENTION;
            Text     = DEFAULT_TEXT + " - " + fileName;

            statusBar2.Visible   = true;
            statusBar2.ForeColor = System.Drawing.Color.DarkGreen;
            statusBar2.Image = System.Drawing.Image.FromFile(goodEx);
            statusBar2.Text  = "Новый файл готов к работе";
            statusBar.Text   = "Готово";

            mniSave.Enabled = false;
            tsbSave.Enabled = false;
        } // new_Click

        #region Формирование списка допустимых значений для ввода через комбо-бокс числовой информации
        // Ввод номера курса, оценки
        // Генерируется список целых значений от from до to и прикрпляется в столбец column
        // проверяем, чтобы соблюдалось условие from < to
        private void SetIntData(int from, int to, DataGridViewColumn column)
        {
            // Этап 1. Создать список значений - объектов класса IntValue
            List<IntData> values = new List<IntData>();

            // Поменять местами переменные from и to, если from > to
            if (from > to) {
                int temp = from;
                from = to;
                to = temp;
            } // if

            // Создать список значений IntValue для отображения в выпадающем списке 
            for (int i = from; i <= to; i++) {
                values.Add(new IntData(i));
            } // for i

            // Добавить специальное значение 0 - для нас оно будет означать отсутствие
            // выбранного из выпадающего списка значаения
            values.Add(new IntData(0));

            // Этап 2. Привязка к столбцу DataGridView
            DataGridViewComboBoxColumn cbc = column as DataGridViewComboBoxColumn;
            cbc.DataSource = values;         // привязка к списку значений
            cbc.ValueMember = "IntValue";    // значения этого свойства возвращать как результат выбора
            cbc.DisplayMember = "StrValue";  // значения этого свойства показыаать в комбо-боксе
        } // SetIntData
        #endregion

        // О программе
        private void mniAbout_Click(object sender, EventArgs e)
        {
            if (aboutForm == null) aboutForm = new AboutForm();
            aboutForm.ShowDialog();
        } // mniAbout_Click


        #region Активность статус-бара
        private void menuItem_MouseEnter(object sender, EventArgs e) {
            statusBar.Text = InfoText[int.Parse((string)((ToolStripMenuItem)sender).Tag)];
        } // menuItem_MouseEnter

        // Событие используем для вывода столбца, не привязанного к источнику данных
        // ирония, в том, что все-таки это данные из коллекции :) :) :)
        // Выполняется форматный вывод в ячейку среднего балла
        private void dgvMain_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // если это новая строка или столбец не столбец среднего балла - выход
            if (dgvMain.Rows[e.RowIndex].IsNewRow ||
                e.ColumnIndex != dgvMain.Columns["dgcAvgLevel"].Index) return;

            // Наша ячейка (ячейка среднего балла) - форматируем вывод
            // в полях параметре e
            e.FormattingApplied = true; 
            double temp = (bnsDataGrid[e.RowIndex] as Student).AvgLevel;
            e.Value = (temp == 0d) ? "" : $"{temp, 5:n2}";
        } // dgvMain_CellFormatting


        // Сортировка данных - общий обработчик для всех сортировок 
        private void mniAnySort_Click(object sender, EventArgs e)
        {
            // Пустая таблица - не сортируем
            if (dgvMain.RowCount == 1) return;

            // Для корректного отображения отсортированной таблицы
            // перейти в начало таблицы
            dgvMain.CurrentCell = dgvMain[0, 0];

            // Получить ссылку на коллекцию данных для упрощения записи
            // выражения сортировки
            List<Student> students = bnsDataGrid.DataSource as List<Student>;

            // Получить режим сортировки по тэгу элемента
            int mode = int.Parse((string)(sender as ToolStripMenuItem).Tag);
            switch (mode) {
                case 1:    // сортировка по фамилии
                    students.Sort((a, b) => a.Surname.CompareTo(b.Surname));
                    break;
                case 2:    // сортировка по среднему баллу - если в сравниваемой паре баллы равны,
                           // то условие сортировки меняем на условие сортировки по фамилии
                           // и далее не погружаемся :) :) 
                    students.Sort((a, b) => {  // блочное лямбда-выражение, реализация правила сортировки
                        int result = Math.Sign(b.AvgLevel - a.AvgLevel);
                        if (result == 0)
                            result = a.Surname.CompareTo(b.Surname);
                        return result;
                    });
                    break;
            } // switch

            // Перечитать данные из источника данных - обновить таблицу
            bnsDataGrid.ResetBindings(false);
        } // mniAnySort_Click

        private void toolItem_MouseEnter(object sender, EventArgs e) {
            statusBar.Text = InfoText[int.Parse((string)((ToolStripButton)sender).Tag)];
        } // toolItem_MouseEnter
        private void otherControls_MouseEnter(object sender, EventArgs e) {
            statusBar.Text = "Готово";
        } // otherControls_MouseEnter
        #endregion
    } // class MainForm
}
