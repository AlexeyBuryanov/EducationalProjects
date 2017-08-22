using InsuranceAgency.Windows;
using Microsoft.Win32;
using System;
using System.Threading;
using System.Windows;

namespace InsuranceAgency
{
    /// <summary>
    /// Логика взаимодействия для App.xaml
    /// </summary>
    public partial class App : Application
    {
        private Mutex mutex;
        public Mutex Mutex { get => mutex; set => mutex = value; }

        public App()
        {
            SplashScreen ss = new SplashScreen(@"Images\splashScreen.png");
            ss.Show(true, true);
            ss.Close(new TimeSpan(0, 0, 2));

            InitializeComponent();

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

            Mutex = new Mutex(true, mutexName, out bool createdNew);

            if (!createdNew) {
                Shutdown();
            } // if
        } // Appl_Startup
    } // class App
}