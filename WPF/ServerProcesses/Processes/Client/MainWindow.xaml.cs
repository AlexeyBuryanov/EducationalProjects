using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using Client.ServiceReference;
using Client.Windows;

namespace Client
{
    public partial class MainWindow : IDisposable
    {
        private readonly ServiceWcfClient _client;
        private ObservableCollection<ProcessProps> ProcessList { get; }


        public MainWindow()
        {
            InitializeComponent();

            ProcessList = new ObservableCollection<ProcessProps>();
            DataGridMain.ItemsSource = ProcessList;

            try {
                _client = new ServiceWcfClient();
                _client.GetProcesses()
                    .ToList()
                    .ForEach(p => {
                    ProcessList.Add(p);
                });
            } catch (Exception e) {
                MessageBox.Show($"{e.Message}", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                TextBlockStatus.Text = "Невозможно связаться с сервером";
            } // try-catch
        } // MainWindow


        /* Обработчики событий
         ******************************************************************************************/

        /// <summary>Выход</summary>
        private void MenuItemExit_OnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        } // MenuItemExit_OnClick


        /// <summary>О программе</summary>
        private void MenuItemAbout_OnClick(object sender, RoutedEventArgs e)
        {
            var win = new AboutWindow(this);
            win.ShowDialog();
        } // MenuItemAbout_OnClick


        /// <summary>Обновить</summary>
        private void ButtonRefresh_OnClick(object sender, RoutedEventArgs e)
        {
            ProcessList.Clear();
            _client.GetProcesses()
                   .ToList()
                   .ForEach(p => {
                       ProcessList.Add(p);
                   });
            TextBlockStatus.Text = "Обновлено";
        } // ButtonRefresh_OnClick


        /// <summary>Старт процесса</summary>
        private async void ButtonStartProcess_OnClickAsync(object sender, RoutedEventArgs e)
        {
            try {
                if (string.IsNullOrWhiteSpace(TextBoxProcessName.Text))
                    return;
                await _client.StartProcessAsync(TextBoxProcessName.Text);
                TextBlockStatus.Text = $"Процесс {TextBoxProcessName.Text} успешно запущен";
                ButtonRefresh_OnClick(sender, e);
            } catch (Exception ex) {
                TextBlockStatus.Text = $"Процесс {TextBoxProcessName.Text} не может быть запущен";
                MessageBox.Show($"{ex.Message}", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            } // try-catch
        } // ButtonStartProcess_OnClickAsync


        /// <summary>Остановка процесса</summary>
        private async void ButtonStopProcess_OnClickAsync(object sender, RoutedEventArgs e)
        {
            try {
                if (string.IsNullOrWhiteSpace(TextBoxProcessName.Text))
                    return;
                await _client.KillProcessAsync(TextBoxProcessName.Text);
                TextBlockStatus.Text = $"Процесс {TextBoxProcessName.Text} успешно остановлен";
                ButtonRefresh_OnClick(sender, e);
            } catch (Exception ex) {
                TextBlockStatus.Text = $"Процесс {TextBoxProcessName.Text} невозможно остановить";
                MessageBox.Show($"{ex.Message}", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            } // try-catch
        } // ButtonStopProcess_OnClickAsync


        /// <summary>Убить процесс по контекстному меню дата грида</summary>
        private async void ContextMenuItemDataGridKillProc_OnClick(object sender, RoutedEventArgs e)
        {
            try {
                if (DataGridMain.SelectedItem is null)
                    return;
                await _client.KillProcessAsync((DataGridMain.SelectedItem as ProcessProps)?.ProcessName);
                TextBlockStatus.Text = $"Процесс {(DataGridMain.SelectedItem as ProcessProps)?.ProcessName} успешно остановлен";
                ButtonRefresh_OnClick(sender, e);
            } catch (Exception ex) {
                TextBlockStatus.Text = $"Процесс {(DataGridMain.SelectedItem as ProcessProps)?.ProcessName} невозможно остановить";
                MessageBox.Show($"{ex.Message}", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            } // try-catch
        } // ContextMenuItemDataGridKillProc_OnClick


        /// <inheritdoc />
        /// <summary>
        /// Реализация интерфейса IDisposable т.к. MainWindow использует IDisposable тип.
        /// Что даёт более эффективное и быстрое завершение работы программы.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        } // Dispose

        // Перегруженный метод с модификатором private и флагом.
        // Анализатор Visual Studio считает, что так правильней.
        private void Dispose(bool value)
        {
            if (!value)
                return;
            _client.Close();
        } // Dispose
    } // MainWindow
} // Client