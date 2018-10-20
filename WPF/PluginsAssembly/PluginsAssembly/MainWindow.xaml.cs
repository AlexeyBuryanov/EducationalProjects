/*
    Разработать приложение для работы с плагинами. Плагин - это .NET сборка с
    расширением dll, лежащая в папке Plugins нашего приложения. Программа
    сканирует папку Plugins и выводит в список названия всех доступных
    плагинов из папки. Пользователь выбирает какой-то плагин и программа
    загружает его (находит нужный класс и нужный метод в сборке). Все
    плагины позволяют как-то изменить внешний вид окна приложения и контролов
    в окне. 
*/


namespace PluginsAssembly
{
    using System;
    using System.Collections.ObjectModel;
    using System.IO;
    using System.Linq;
    using System.Reflection;
    using System.Threading.Tasks;
    using System.Windows;
    using System.Windows.Input;
    using System.Windows.Media;
    using System.Windows.Threading;

    public partial class MainWindow
    {
        private readonly ObservableCollection<string> _plugList;
        private readonly string _pathToPlugins;
        private readonly DispatcherTimer _timer;
        private string[] _files;
        

        public MainWindow()
        {
            InitializeComponent();

            _plugList = new ObservableCollection<string>();
            ListBoxPlugins.ItemsSource = _plugList;

            _pathToPlugins = "Plugins";
            Directory.CreateDirectory(_pathToPlugins);

            _timer = new DispatcherTimer();
            _timer.Tick += Timer_TickAsync;
            _timer.Interval = new TimeSpan(0, 0, 1);
            _timer.Start();
        } // MainWindow


        private async void Timer_TickAsync(object sender, EventArgs e)
        {
            try {
                await ScanningForPluginsAsync(_pathToPlugins);
            } catch (Exception ex) {
                MessageBox.Show($"Сканирование на наличие плагинов будет остановлено.\n\n{ex.Message}", 
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                _timer.Stop();
            } // try-catch
        } // Timer_TickAsync


        /// <summary>
        /// Скан на наличие плагинов
        /// </summary>
        /// <param name="path">Путь</param>
        public Task ScanningForPluginsAsync(string path)
        {
            return Task.Factory.StartNew(() => {
                Dispatcher.Invoke(() => {
                    _plugList.Clear();
                });
                _files = Directory.GetFiles(_pathToPlugins);

                _files
                .Where(f => f.EndsWith(".dll"))
                .ToList()
                .ForEach(async s => {
                    try {
                        Assembly.LoadFrom(s);
                        await Dispatcher.InvokeAsync(() => {
                            _plugList.Add(s.Remove(s.LastIndexOf(".", StringComparison.Ordinal)).Substring(s.IndexOf(@"\", StringComparison.Ordinal) + 1));
                        });
                    } catch (BadImageFormatException) {
                        // ignored
                    } // try-catch
                });
            });
        } // ScanningForPluginsAsync


        private void MenuItemExit_OnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        } // MenuItemExit_OnClick


        private void ListBoxPlugins_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (ListBoxPlugins.SelectedItem == null)
                return;

            _files
                .ToList()
                .ForEach(assemblyName => {
                    if (assemblyName.Substring(assemblyName.IndexOf(@"\", StringComparison.Ordinal)+1) != (string)ListBoxPlugins.SelectedItem+".dll")
                        return;

                    Assembly.LoadFrom(assemblyName)
                            .GetTypes()
                            .ToList()
                            .ForEach(t => {
                                t.GetMethods(BindingFlags.Public | BindingFlags.Instance)
                                    .ToList()
                                    .ForEach(m => {
                                        switch (m.Name) {
                                            case "SetWindowStyle": {
                                                var obj = Activator.CreateInstance(t);
                                                var arg = new object[1];
                                                Visibility = Visibility.Collapsed;
                                                arg[0] = this;
                                                m.Invoke(obj, arg);
                                                Visibility = Visibility.Visible;
                                                break;
                                            } // SetTheme
                                            case "SetBackgroundWindow": {
                                                var obj = Activator.CreateInstance(t);
                                                var arg = new object[1];
                                                arg[0] = this;
                                                m.Invoke(obj, arg);
                                                break;
                                            } // SetBackgroundWindow
                                            case "SetBackgroundWindowFrom": {
                                                StackPanelInputColor.Visibility = Visibility.Visible;
                                                var obj = Activator.CreateInstance(t);
                                                var arg = new object[2];
                                                arg[0] = this;
                                                arg[1] = new SolidColorBrush(Color.FromRgb(Convert.ToByte(TextBoxR.Text), Convert.ToByte(TextBoxG.Text), Convert.ToByte(TextBoxB.Text)));
                                                m.Invoke(obj, arg);
                                                break;
                                            } // SetBackgroundWindowFrom
                                        } // switch
                                    });
                            });
                });
        } // ListBoxPlugins_MouseDoubleClick


        private void TextBox_OnPreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            if (!char.IsDigit(e.Text, 0))
                e.Handled = true;
        } // TextBox_OnPreviewTextInput
    } // MainWindow class
} // PluginsAssembly