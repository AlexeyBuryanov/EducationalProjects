using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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

namespace Car_company
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private XmlSerializer formatter;
        private const string fileName = @"...\...\buses.dat";
        private List<DataBus> buses;


        public MainWindow()
        {
            InitializeComponent();
            formatter = new XmlSerializer(typeof(List<DataBus>));
            buses = LoadData();
            dataGridMain.ItemsSource = buses;
        } // MainWindow


        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        } // Exit_Click


        private void aboutWinShow_Click(object sender, RoutedEventArgs e)
        {
            AboutWindow win = new AboutWindow();
            win.ShowDialog();
        } // aboutWinShow_Click


        private List<DataBus> LoadData()
        {
            List<DataBus> temp = null;

            if (File.Exists(fileName)) {
                using (StreamReader sr = new StreamReader(fileName, Encoding.UTF8)) {
                    temp = (List<DataBus>)formatter.Deserialize(sr);
                } // using
            } // if

            return temp;
        } // LoadData

        
        private void Window_Closed(object sender, EventArgs e)
        {
            using (StreamWriter sw = new StreamWriter(fileName, false, Encoding.UTF8)) {
                formatter.Serialize(sw, buses);
            } // using
        } // Window_Closed

 
        private void Remove_Click(object sender, RoutedEventArgs e)
        {
            if (dataGridMain.SelectedItem == null) return;
            DataBus bus = (DataBus)dataGridMain.SelectedItem;
            buses.Remove(bus);
            dataGridMain.ItemsSource = null;
            dataGridMain.ItemsSource = buses;
        } // Remove_Click
    } // class MainWindow : Window
}
