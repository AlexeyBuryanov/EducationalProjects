using System.Windows;
using Microsoft.Win32;

namespace HtmlDownloader
{
    class DefaultDialogService : IDialogService
    {
        public string FilePath { get; set; }

        public bool OpenFileDialog()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog() {
                InitialDirectory = @"d:\",
                Filter = "HTML (*.html)|*.html|Все файлы (*.*)|*.*",
                Multiselect = false,
                ValidateNames = true,
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
                Filter = "HTML (*.html)|*.html|Все файлы (*.*)|*.*",
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
} // HtmlDownloader