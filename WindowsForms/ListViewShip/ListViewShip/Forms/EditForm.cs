using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace ListViewShip.Forms
{
    public partial class EditForm : Form
    {
        private string fileName = @"";  // имя файла с фотографией

        // Свойство Data - для связи формы с внешним миром
        // При присваивании эьому свойству поля данных записываются
        // (с преобразованием) в соответствующие поля ввода

        // При чтении этого свойства из полей данных (с преобразованием)
        // извлекаются данные и направляются в объект класса Ship 

        // TODO: обеспечить корректность ввода данных в поля txbDisplacement,
        //       txbMaxSpeed, txbCruisingRange
        // TODO: Если добавить корабль с фото, а следом добавить ещё одну запись, но уже без фото, 
        //       то эта запись уже будет не без фото (как предполагалось), а с фото предыдущей записи.
        //       Запоминается старый путь, но, как сделать, чтобы не было такого...
        public Ship Data {
            // Геттер работаем при приеме данных из внешних форм
            get {
                Ship ship = new Ship() {
                    Name = txbName.Text,
                    Displacement = int.Parse(txbDisplacement.Text),
                    Speed = double.Parse(txbMaxSpeed.Text),
                    CruisingRange = int.Parse(txbCruisingRange.Text),
                    FilePhoto = fileName
                };
                return ship; 
            } // get

            // Сеттер работает при передаче данных во внешние формы
            set {
                txbName.Text = value.Name;
                txbDisplacement.Text = $"{value.Displacement}";
                txbMaxSpeed.Text = $"{value.Speed}";
                txbCruisingRange.Text = $"{value.CruisingRange}";

                // Если фото корабля есть в папке, то загрузить его
                // Иначе - загрузить картинку-заполнитель (это статическое свойство главной формы)
                fileName = value.FilePhoto;  // Важно! Надо запомнить имя файла!
                pbxPhoto.Load(File.Exists(value.FilePhoto) ? value.FilePhoto : (MainForm.folderImages + Ship.fileNoPhoto));
            } // set
        } // Ship


        // Очистка полей ввода
        public void Clear()
        {
            txbName.Text = txbDisplacement.Text = txbMaxSpeed.Text = txbCruisingRange.Text = "";
            pbxPhoto.Load(MainForm.folderImages + Ship.fileNoPhoto);  // это статическое свойство главной формы
        } // Clear


        // Конструктор формы
        public EditForm() { InitializeComponent(); } // EditForm


        // Выбор фотографии корабля, установка в pbxPhoto, запоминание имени файла
        // с картинкой для дальнейшего копирования в папку фоток коллекции
        private void btnPhotoChoice_Click(object sender, EventArgs e)
        {
            if (ofdPhoto.ShowDialog() != DialogResult.OK) return;

            fileName = ofdPhoto.FileName;   // Запомнить имя файла
            pbxPhoto.Load(fileName);        // Загрузить файл в элемент отображения 
        } // btnPhotoChoice_Click


        // Если хоть в одном поле ввода пустота - ввод не возможен
        private void txbAll_TextChanged(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txbName.Text)
                || string.IsNullOrWhiteSpace(txbDisplacement.Text)
                || string.IsNullOrWhiteSpace(txbMaxSpeed.Text)
                || string.IsNullOrWhiteSpace(txbCruisingRange.Text))
                btnSaveOk.Enabled = false;
            else
                btnSaveOk.Enabled = true;
        } // txbAll_TextChanged
	} // class EditForm
}
