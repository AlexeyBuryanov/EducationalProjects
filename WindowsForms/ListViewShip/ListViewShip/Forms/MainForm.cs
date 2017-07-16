using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ListViewShip
{
    public partial class MainForm : Form
    {
        static readonly string[] InfoText = {
            "Файл",
            "Создать новую коллекцию", "Открыть существующую коллекцию", "Сохранить текущую коллекцию",
            "Сохранить как...", "Завершить работу приложения",
            "Операции",
            "Добавить данные о корабле", "Удалить выбранный корабль", "Редактировать выбранный корабль",
            "Справка",
            "Информация о программе"
        };

        // имя корневой папки с фотографиями коллекций
        public static readonly string folderImages = @"..\..\Images\";

        Ships ships;      // коллекция кораблей
        string fileName;  // файл для сохранения/загрузки
        bool isAddOrEdit; // флаг сообщающий осуществлялось ли добавление/изменение записи
        List<string> addedImages;   // список со всеми именами фото добавленных кораблей (на текущий момент)
        Forms.EditForm editForm;    // форма для ввода/редактирования данных о корабле
        Forms.AboutForm aboutForm;  // форма инфо о программе
        public MainForm()
        {
            InitializeComponent();

            // Создать коллекцию кораблей, связь коллекции с элементом
            // интерфейса ListView
            ships = new Ships();

            // Создать коллекцию добавленных изображений
            addedImages = new List<string>();

            // для надежности, т.к. в конструкторах может отсутствовать передача
            // ссылки на ListView в списке параметров, и еще - как через конструктор
            // по умолчанию связаться с ListView? да никак - вот и нужно свойство 
            ships.ShipListView = lvShips;

            // Фото корабля по умолчанию
            pbxShip.Load((folderImages + Ship.fileNoPhoto));

            isAddOrEdit = false;
        } // MainForm


        // Добавление записи в ListView по команде меню (инструментальной кнопке)
        private void mniAdd_Click(object sender, EventArgs e)
        {
            statusBar.Text = "Добавление записи...";

            // Открепляем текущее фото от пикчер-бокса
            pbxShip.Load((folderImages + Ship.fileNoPhoto));

            if (editForm == null) editForm = new Forms.EditForm();
            editForm.Text = "Добавление корабля в коллекцию";
            // при добавлении все поля ввода д.б. пустыми 
            // в том числе и внутренний пикчер-бокс
            editForm.Clear(); 
            if (editForm.ShowDialog() != DialogResult.OK) return;

            // Прочитать данные из формы
            Ship ship = editForm.Data;

            // перед добавлением - копировать файл в папку Images проекта,
            // скорректировать имя файла - привести к формату Images\ИмяФайла
            if (!string.IsNullOrEmpty(ship.FilePhoto)) {
                // новое имя - файл приемник
                string temp = folderImages + ship.Name + Path.GetExtension(ship.FilePhoto); 
                if (!File.Exists(temp)) {
                    addedImages.Add(temp);            // добавляем имя файла в список
                    File.Copy(ship.FilePhoto, temp);  // копирование из старого места в папку Images проекта
                } // if 
                ship.FilePhoto = temp;  // запомнить новое имя файла
            } // когда пользователь не выбирает фотографию новому кораблю
            else ship.FilePhoto = (folderImages + Ship.fileNoPhoto);

            ships.Add(ship);  // и, наконец-таки, добавляем корабль

            // Добавить элемент в ListView"
            // a) создать элемент - первый столбец ListView
            ListViewItem item = new ListViewItem($"{ship.Id}");

            // б) создать подэлементы - остальные столбцы
            item.SubItems.Add(ship.Name);
            item.SubItems.Add($"{ship.Displacement}");
            item.SubItems.Add($"{ship.Speed}");
            item.SubItems.Add($"{ship.CruisingRange}");

            // в) собственно добавление в ListView
            lvShips.Items.Add(item);

            statusBar.Text = "Корабль добавлен в коллекцию";

            // После добавления записи делать активной последнюю запись, которая добавлена
            lvShips.Items[lvShips.Items.Count-1].Selected = true;

            isAddOrEdit = true;
            mniSave.Enabled = true;
            mniSaveAs.Enabled = true;
        } // mniAdd_Click


        // Удаление записи из ListView по команде меню (инструментальной кнопке)
        private void mniRemove_Click(object sender, EventArgs e)
        {
            // проверка - есть ли выбранные элементы
            if (lvShips.SelectedIndices.Count == 0) {
                MessageBox.Show("Корабль для удаления не выбран", "Ошибка", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            } // if

            // удаление при помощи "делегированного" метода класса List
            int index = lvShips.SelectedIndices[0];  // индекс выбранного элемента

            // Получить имя файла картинки удаляемого корабля
            string fileName = ships[index].FilePhoto;

            ships.RemoveAt(index);         // удаление из контейнерного класса          
            lvShips.Items.RemoveAt(index); // удаление из элемента интерфейса
            // Открепить изображение от пикчер-бокса
            pbxShip.Load(folderImages + Ship.fileNoPhoto);

            // Обход ситуации, если пользователь не выбрал фотографию
            if (fileName != (folderImages + Ship.fileNoPhoto)) {
                // Удалить файл из папки Images
                if (File.Exists(fileName)) {
                    File.Delete(fileName);
                } // if
            } // if

            statusBar.Text = "Запись успешно удалена";

            // После удаления записи делать активной запись, которая была перед удалённой
            if (lvShips.Items.Count > 0) {
                lvShips.Items[index - 1].Selected = true;
            } // if
        } // mniRemove_Click


        // Обработка команды - редактирование корабля в коллекции
        // (обработка меню и кнопки панели инструментов)
        // TODO: И всё таки по результатам тестирования, если провести запись 
        //       и тут же попробовать изменить ей фото, то замена фото не проходит!!
        //       Не могу понять почему (?)
        private void mniEdit_Click(object sender, EventArgs e)
        {
            statusBar.Text = "Редактирование...";

            // Проверка, есть или нет выбранного элемента в списке ListView - 
            // сообщить об ошибке и выйти
            if (lvShips.SelectedIndices.Count == 0) {
                MessageBox.Show("Корабль для редактирования не выбран", "Ошибка",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            } // if

            // Получить индекс выбранного корабля
            int index = lvShips.SelectedIndices[0];

            // Создание формы, при необходимости, настройка формы
            // а) название, соответствующее операции формы - редактированию
            // б) передать данные в форму
            if (editForm == null) editForm = new Forms.EditForm();
            editForm.Text = "Изменение (редактирование) данных корабля в коллекции";
            editForm.Data = ships[index];

            if (editForm.ShowDialog() != DialogResult.OK) return;

            // Прочитать данные из формы, записать их новые значения
            // в коллекцию кораблей, в ListView 
            Ship ship = editForm.Data;
            editForm.Clear(); // Очистка полей, отсоединение от файла фотографии

            // !!! Идея работы с файлами фотографий
            // а) получаем имя файла-источника в форме редактирования
            // б) передаем в главную форму полное имя файла
            // в) в главной форме из имени файла, полученного из формы ввода (возможно,
            //    это полное имя, возмозжно - имя в папке Images) делаем
            //    имя из Images + толькоИмяФайле
            // г) проверяем, есть ли такой файл в папке Images
            //    и если его нет - копируем и заменяем имя файла источника
            //    именем файла-копии в папке Images
            // перед записью в коллекцию - копировать файл фото в папку Images проекта, если этого
            // файла еще нет в папке фотографий кораблей
            // скорректировать имя файла - привести к формату Images\ИмяФайла
            string temp = folderImages + ship.Name + Path.GetExtension(ship.FilePhoto); // новое имя - файл приемник
            if (!File.Exists(temp)) {
                addedImages.Add(temp);            // добавляем имя файла в список
                File.Copy(ship.FilePhoto, temp);  // копирование из старого места в папку Images проекта
            } // if 
            ship.FilePhoto = temp;    // запомнить новое имя файла

            ships[index] = ship;      // копируются все поля, кроме идентификатора

            // Заменить поля элемента в ListView
            // a) получить элемент index из ListView
            ListViewItem item = lvShips.Items[index];

            // б) записать новые значения столбцов
            item.SubItems[0].Text = $"{ship.Id}";
            item.SubItems[1].Text = ship.Name;
            item.SubItems[2].Text = $"{ship.Displacement}";
            item.SubItems[3].Text = $"{ship.Speed}";
            item.SubItems[4].Text = $"{ship.CruisingRange}";

            // в) собственно замена в ListView по индексу index
            lvShips.Items[index] = item;

            statusBar.Text = "Запись изменена";

            // После изменения записи делать активной запись, которая была изменена
            lvShips.Items[index].Selected = true;

            isAddOrEdit = true;
        } // mniEdit_Click


        // Выход из приложения по команде меню (инструментальной кнопке)
        private void mniExit_Click(object sender, EventArgs e)
        {
            // NOTE: Такая обработка работает только, если юзер выходит по нашей кнопке выхода.
            //       А что делать, если пользователь по привычке жмёт на крестик?

            // Если записи не добавлялись и не редактировались молча выходим
            if (!isAddOrEdit) Application.Exit();

            DialogResult reply = MessageBox.Show(
                "Выйти из программы? Все несохранённые данные будут утеряны.", "Выход", 
                MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (reply == DialogResult.Yes) {
                // Удаляем все добавленные (на текущий момент времени) 
                // изображения из папки накопления Images
                foreach (var image in addedImages) {
                    pbxShip.Load(folderImages + Ship.fileNoPhoto);
                    File.Delete(image);
                } // foreach
                Application.Exit();
            } // if
        } // mniExit_Click


        // Сохранить коллекцию кораблей в файле - бинарная сериализация
        // (обработка меню и кнопки панели инструментов)
        private void mniSave_Click(object sender, EventArgs e)
        {
            statusBar.Text = "Сохранение...";

            // Если имя файла уже задано, не выводим диалог выбора файла
            if (string.IsNullOrEmpty(fileName)) {
                // Выбираем/задаем файл для сохранения, если не задан - уходим 
                if (sfdMain.ShowDialog() != DialogResult.OK) return;

                // Запомнить имя файла и сохранить коллекцию в этом файле
                fileName = sfdMain.FileName;
            } // if
         
            ships.Save(fileName);
            Text = "Коллекция кораблей, файл - " + fileName;
            statusBar.Text = "Файл успешно сохранён";
        } // mniSave_Click


        // Сохранить как (только меню)
        private void mniSaveAs_Click(object sender, EventArgs e)
        {
            statusBar.Text = "Сохранение...";

            // Выбираем/задаем файл для сохранения, если не задан - уходим 
            if (sfdSaveAs.ShowDialog() != DialogResult.OK) return;

            // Запомнить имя файла и сохранить коллекцию в этом файле
            fileName = sfdSaveAs.FileName;

            ships.Save(fileName);
            Text = "Коллекция кораблей, файл - " + fileName;
            statusBar.Text = "Файл успешно сохранён";
        } // mniSaveAs_Click


        // Очистка данных
        // (обработка меню и кнопки панели инструментов)
        private void mniNew_Click(object sender, EventArgs e)
        {
            lvShips.Items.Clear();
            ships.Clear();
            fileName = "";
            Text = "Коллекция кораблей";
            pbxShip.Load(folderImages + Ship.fileNoPhoto);   // очистка поля отображения фото
            statusBar.Text = "Новая коллекция готова к заполнению";
            mniSave.Enabled = false;
            mniSaveAs.Enabled = false;
        } // mniNew_Click


        // Загрузка файла данных, десериализация
        // (обработка меню и кнопки панели инструментов)
        private void mniOpen_Click(object sender, EventArgs e)
        {
            statusBar.Text = "Открытие...";

            // Выбрать файл для загрузки
            if (ofdMain.ShowDialog() != DialogResult.OK) return;
            fileName = ofdMain.FileName;

            // Загрузить данные в коллекцию, в элемент отображения
            ships.Load(fileName);  // загрузка в коллекцию
            LoadFromShips();       // копирование коллекции в ListView
            pbxShip.Load(folderImages + Ship.fileNoPhoto);   // очистка поля отображения фото
            Text = "Коллекция кораблей, файл - " + fileName; // коррекция заголовка окна
            statusBar.Text = "Файл успешно открыт";
            mniSave.Enabled = true;
            mniSaveAs.Enabled = true;
        } // mniOpen_Click


        // Очистка ListView, копирование из коллекции в ListVew
        private void LoadFromShips()
        {
            lvShips.Items.Clear();

            // Перебираем коллекцию кораблей
            foreach (Ship ship in ships) {
                // Добавить элемент в ListView"
                // a) создать элемент - первый столбец ListView
                ListViewItem item = new ListViewItem($"{ship.Id}");

                // б) создать подэлементы - остальные столбцы
                item.SubItems.Add(ship.Name);
                item.SubItems.Add($"{ship.Displacement}");
                item.SubItems.Add($"{ship.Speed}");
                item.SubItems.Add($"{ship.CruisingRange}");

                // в) собственно добавление в ListView
                lvShips.Items.Add(item);
            } // foreach
            statusBar.Text = "Загрузка...";
        } // LoadFromShips


        // Выполнить редактирование корабля по двойному щелчку мышью
        private void lvShips_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            mniEdit_Click(mniEdit, EventArgs.Empty);
        } // lvShips_MouseDoubleClick


        // Отображение фотографии корабля при изменении выбранного элемента в списке
        private void lvShips_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Защита от ситуации, когда выбор еще не выполнен, т.е.
            // нет выбранной строки в ListView 
            if (lvShips.SelectedIndices.Count == 0) return;

            int index = lvShips.SelectedIndices[0];
            string fileName = ships[index].FilePhoto;
            pbxShip.Load(File.Exists(fileName) ? fileName : (folderImages + Ship.fileNoPhoto));
        } // lvShips_SelectedIndexChanged


        // О программе
        private void mniAbout_Click(object sender, EventArgs e)
        {
            if (aboutForm == null) aboutForm = new Forms.AboutForm();
            aboutForm.ShowDialog();
        } // mniAbout_Click


        #region Активность статус-бара по наведению курсором на элементы меню и панели инструментов
        private void menuItem_MouseEnter(object sender, EventArgs e)
        {
            statusBar.Text = InfoText[int.Parse((string)((ToolStripMenuItem)sender).Tag)];
        }
        private void tsbNew_MouseEnter(object sender, EventArgs e)
        {
            statusBar.Text = InfoText[int.Parse((string)((ToolStripButton)sender).Tag)];
        }
        private void otherControls_MouseEnter(object sender, EventArgs e)
        {
            statusBar.Text = "Готово";
        }
        #endregion
    } // class MainForm
}
