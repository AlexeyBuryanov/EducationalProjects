using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;

namespace SimpleDrawings
{
    public class ApplicationViewModel : INotifyPropertyChanged
    {
        private MainWindow _mainWindow;
        private Grid _gridRocket, _gridShip, _gridClown;
        private Image _pics;

        public ApplicationViewModel(MainWindow mainWindow)
        {
            _mainWindow = mainWindow;
            _gridRocket = (Grid)_mainWindow.FindName("gridRocket");
            _gridShip = (Grid)_mainWindow.FindName("gridShip");
            _gridClown = (Grid)_mainWindow.FindName("gridClown");
            _pics = (Image)_mainWindow.FindName("pics");

            //***** СОЗДАНИЕ КОМАНД *****//
            ExitCommand   = new RelayCommand(Exit);
            RocketCommand = new RelayCommand(Rocket);
            ShipCommand   = new RelayCommand(Ship);
            ClownCommand  = new RelayCommand(Clown);
        } // ApplicationViewModel

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged([CallerMemberName]string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        } // OnPropertyChanged

        //********************************* КОМАНДЫ ***********************************//
        // Выход
        private RelayCommand _exitCommand;
        public RelayCommand ExitCommand {
            get { return _exitCommand; }
            set { _exitCommand = value; }
        } // ExitCommand

        // Ракета
        private RelayCommand _rocketCommand;
        public RelayCommand RocketCommand {
            get { return _rocketCommand; }
            set { _rocketCommand = value; }
        } // RocketCommand

        // Кораблик
        private RelayCommand _shipCommand;
        public RelayCommand ShipCommand {
            get { return _shipCommand; }
            set { _shipCommand = value; }
        } // ShipCommand

        // Клоун
        private RelayCommand _clownCommand;
        public RelayCommand ClownCommand {
            get { return _clownCommand; }
            set { _clownCommand = value; }
        } // ClownCommand

        //**************************** РЕАЛИЗАЦИИ КОМАНД ******************************//

        // Выход
        private void Exit(object obj)
        {
            Application.Current.Shutdown();
        } // Exit

        // Ракета
        private void Rocket(object obj)
        {
            _pics.Visibility = Visibility.Collapsed;
            // Скрываем кораблик с клоуном
            _gridShip.Visibility = Visibility.Collapsed;
            _gridClown.Visibility = Visibility.Collapsed;

            // Показываем ракету
            _gridRocket.Visibility = Visibility.Visible;
        } // Rocket

        // Корабль
        private void Ship(object obj)
        {
            _pics.Visibility = Visibility.Collapsed;
            // Скрываем ракету с клоуном
            _gridRocket.Visibility = Visibility.Collapsed;
            _gridClown.Visibility = Visibility.Collapsed;

            // Показываем кораблик
            _gridShip.Visibility = Visibility.Visible;
        } // Ship

        // Клоун
        private void Clown(object obj)
        {
            _pics.Visibility = Visibility.Collapsed;
            // Скрываем кораблик с ракетой
            _gridShip.Visibility = Visibility.Collapsed;
            _gridRocket.Visibility = Visibility.Collapsed;

            // Показываем клоуна
            _gridClown.Visibility = Visibility.Visible;
        } // Clown
    } // class ApplicationViewModel
} // namespace WpfPractice