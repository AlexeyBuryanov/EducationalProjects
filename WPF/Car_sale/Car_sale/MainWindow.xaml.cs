using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Xml.Serialization;

namespace Car_sale
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private List<Car> cars;
        private Car car;
        private XmlSerializer formatter;
        private const string fileName = ".../.../cars.dat";

        public MainWindow()
        {
            InitializeComponent();
            cars = new List<Car>();
            car = new Car();
            car.Optional = new Optional();
            formatter = new XmlSerializer(typeof(List<Car>));
            car.TransportCategory = radioButton_Passenger.Content.ToString();
            car.TypePayment       = radioButton_Cash.Content.ToString();
            radioButton_Passenger.Checked += RadioButton_Checked;
            radioButton_Cargo.Checked     += RadioButton_Checked;
            radioButton_Special.Checked   += RadioButton_Checked;
            radioButton_Cash.Checked     += RadioButton_Checked;
            radioButton_Cards.Checked    += RadioButton_Checked;
            radioButton_Ewallets.Checked += RadioButton_Checked;
            checkBox_Recorder.Checked    += checkBox_Checked;
            checkBox_Acoustics.Checked   += checkBox_Checked;
            checkBox_Navigator.Checked   += checkBox_Checked;
            checkBox_Conditioner.Checked += checkBox_Checked;
            checkBox_Computer.Checked    += checkBox_Checked;
            checkBox_Recorder.Unchecked    += checkBox_Unchecked;
            checkBox_Acoustics.Unchecked   += checkBox_Unchecked;
            checkBox_Navigator.Unchecked   += checkBox_Unchecked;
            checkBox_Conditioner.Unchecked += checkBox_Unchecked;
            checkBox_Computer.Unchecked    += checkBox_Unchecked;
        } // MainWindow


        private void LoadData()
        {
            if (File.Exists(fileName)) {
                using (StreamReader sr = new StreamReader(fileName, Encoding.UTF8)) {
                    cars = (List<Car>)formatter.Deserialize(sr);
                } // using
            } // if
        } // LoadData


        private void button_Write_Click(object sender, RoutedEventArgs e)
        {
            LoadData();
            car.Manufacturer = textBox_Manufacturer.Text;
            cars.Add(car);
            using (StreamWriter sw = new StreamWriter(fileName, false, Encoding.UTF8)) {
                formatter.Serialize(sw, cars);
            } // using
        } // button_Write_Click


        private void button_Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        } // button_Exit_Click


        private void button_About_Click(object sender, RoutedEventArgs e)
        {
            AboutWindow win = new AboutWindow();
            win.Show();
        } // button_About_Click


        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            RadioButton rb = (sender as RadioButton);
            if (rb.GroupName == "transport") {
                car.TransportCategory = rb.Content.ToString();
            } else {
                car.TypePayment = rb.Content.ToString();
            } // if
        } // RadioButton_Checked


        private void checkBox_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox cb = (sender as CheckBox);
            if (cb == checkBox_Recorder)
                car.Optional.criterion1 = cb.Content.ToString();
            else if (cb == checkBox_Acoustics)
                car.Optional.criterion2 = cb.Content.ToString();
            else if (cb == checkBox_Navigator)
                car.Optional.criterion3 = cb.Content.ToString();
            else if (cb == checkBox_Conditioner)
                car.Optional.criterion4 = cb.Content.ToString();
            else if (cb == checkBox_Computer)
                car.Optional.criterion5 = cb.Content.ToString();
        } // checkBox_Checked


        private void checkBox_Unchecked(object sender, RoutedEventArgs e)
        {
            CheckBox cb = (sender as CheckBox);
            if (cb == checkBox_Recorder)
                car.Optional.criterion1 = "*не выбрано*";
            else if (cb == checkBox_Acoustics)
                car.Optional.criterion2 = "*не выбрано*";
            else if (cb == checkBox_Navigator)
                car.Optional.criterion3 = "*не выбрано*";
            else if (cb == checkBox_Conditioner)
                car.Optional.criterion4 = "*не выбрано*";
            else if (cb == checkBox_Computer)
                car.Optional.criterion5 = "*не выбрано*";
        } // checkBox_Unchecked


        private void radioButton_Passenger_MouseEnter(object sender, MouseEventArgs e)
        {
            popupPassenger.IsOpen = true;
        } // radioButton_Passenger_MouseEnter

        private void radioButton_Cargo_MouseEnter(object sender, MouseEventArgs e)
        {
            popupCargo.IsOpen = true;
        } // radioButton_Cargo_MouseEnter

        private void radioButton_Special_MouseEnter(object sender, MouseEventArgs e)
        {
            popupSpec.IsOpen = true;
        } // radioButton_Special_MouseEnter

        private void radioButton_Cash_MouseEnter(object sender, MouseEventArgs e)
        {
            popupCash.IsOpen = true;
        } // radioButton_Cash_MouseEnter

        private void radioButton_Cards_MouseEnter(object sender, MouseEventArgs e)
        {
            popupCards.IsOpen = true;
        } // radioButton_Cards_MouseEnter

        private void radioButton_Ewallets_MouseEnter(object sender, MouseEventArgs e)
        {
            popupEwallets.IsOpen = true;
        } // radioButton_Ewallets_MouseEnter
    } // class MainWindow
}
