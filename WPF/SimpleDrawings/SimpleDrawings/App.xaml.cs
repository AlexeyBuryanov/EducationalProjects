using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace SimpleDrawings
{
    /// <summary>
    /// Логика взаимодействия для App.xaml
    /// </summary>
    public partial class App : Application
    {
        Mutex mutex;

        public App()
        {
            // Перехват необработанных исключений
            DispatcherUnhandledException += (e, arg) =>
                MessageBox.Show(arg.Exception.Message, "Ошибка",
                MessageBoxButton.OK, MessageBoxImage.Error);
        } // App


        // Точка входа приложения
        [STAThread]
        static void Main()
        {
            App app = new App();
            MainWindow win = new MainWindow();
            app.Run(win);
        }  // Main


        // Запуск только одного экземпляра приложения
        private void App_Startup(object sender, StartupEventArgs e)
        {
            string mutexName = "AppMutexUnique123";

            mutex = new Mutex(true, mutexName, out bool createdNew);

            if (!createdNew) {
                Shutdown();
            } // if
        } // Appl_Startup
    } // class App
}
