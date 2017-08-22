﻿using System.Windows;

namespace SimpleDrawings
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new ApplicationViewModel(this);
        } // MainWindow
    } // class MainWindow
}