using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;
using System.Windows;

namespace InsuranceAgency
{
    public class DefaultDialogService : IDialogService
    {
        public string FilePath { get; set; }

        public bool OpenFileDialog()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog() {
                InitialDirectory = @"d:\",
                Filter = "Images (*.jpg;*.png;*bmp;*gif)|*.jpg;*png;*bmp;*gif|Все файлы (*.*)|*.*",
                Multiselect = false,
                ValidateNames = true,
                Title = "Изменение фото"
            };
            if (openFileDialog.ShowDialog() == true) {
                FilePath = openFileDialog.FileName;
                return true;
            } // if
            return false;
        } // OpenFileDialog

        public bool SaveFileDialog()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog() {
                InitialDirectory = @"d:\",
                Filter = "Images (*.jpg;*.png;*bmp;*gif)|*.jpg;*png;*bmp;*gif|Все файлы (*.*)|*.*",
                ValidateNames = true
            };
            if (saveFileDialog.ShowDialog() == true) {
                FilePath = saveFileDialog.FileName;
                return true;
            } // if
            return false;
        } // SaveFileDialog

        public void ShowError(string message)
        {
            MessageBox.Show(message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
        } // ShowError
    } // class DefaultDialogService
}
