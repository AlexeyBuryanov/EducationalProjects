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

namespace WPF_Containers
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        } // MainWindow


        private void button_Grid_Click(object sender, RoutedEventArgs e)
        {
            Grid win = new Grid();
            win.Show();
        } // button_Grid_Click


        private void button_Stack_Click(object sender, RoutedEventArgs e)
        {
            Stack win = new Stack();
            win.Show();
        } // button_Stack_Click


        private void button_Dock_Click(object sender, RoutedEventArgs e)
        {
            Dock win = new Dock();
            win.Show();
        } // button_Dock_Click


        private void button_Canvas_Click(object sender, RoutedEventArgs e)
        {
            Canvas win = new Canvas();
            win.Show();
        } // button_Canvas_Click


        private void button_About_Click(object sender, RoutedEventArgs e)
        {
            AboutWindow win = new AboutWindow();
            win.Show();
        } // button_About_Click


        private void button_Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        } // button_Exit_Click
    }
}
