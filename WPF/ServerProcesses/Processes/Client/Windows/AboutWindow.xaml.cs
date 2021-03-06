﻿using System.Reflection;
using System.Windows;
using System.Windows.Input;

namespace Client.Windows
{
    /// <summary>
    /// Логика взаимодействия для AboutWindow.xaml
    /// </summary>
    public partial class AboutWindow : Window
    {
        public AboutWindow()
        {
            InitializeComponent();

            ProductName.Text = AssemblyProduct;
            Version.Text     = $"Версия {AssemblyVersion}";
            Copyright.Text   = AssemblyCopyright;
            CompanyName.Text = AssemblyCompany;
            Description.Text = AssemblyDescription;
        } // AboutWindow

        public AboutWindow(Window owner) : this()
        {
            InitializeComponent();

            ProductName.Text = AssemblyProduct;
            Version.Text     = $"Версия {AssemblyVersion}";
            Copyright.Text   = AssemblyCopyright;
            CompanyName.Text = AssemblyCompany;
            Description.Text = AssemblyDescription;

            Owner = owner;
        } // AboutWindow


        #region Методы доступа к атрибутам сборки
        // Заголовок программы
        public string AssemblyTitle {
            get {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyTitleAttribute), false);
                if (attributes.Length > 0) {
                    AssemblyTitleAttribute titleAttribute = (AssemblyTitleAttribute)attributes[0];
                    if (titleAttribute.Title != "") {
                        return titleAttribute.Title;
                    } // if
                } // if
                return System.IO.Path.GetFileNameWithoutExtension(Assembly.GetExecutingAssembly().CodeBase);
            } // get
        } // AssemblyTitle

        // Версия
        public string AssemblyVersion {
            get {
                return Assembly.GetExecutingAssembly().GetName().Version.ToString();
            } // get
        } // AssemblyVersion

        // Описание
        public string AssemblyDescription {
            get {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyDescriptionAttribute), false);
                if (attributes.Length == 0) {
                    return "";
                } // if
                return ((AssemblyDescriptionAttribute)attributes[0]).Description;
            } // get
        } // AssemblyDescription

        // Имя продукта (приложения)
        public string AssemblyProduct {
            get {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyProductAttribute), false);
                if (attributes.Length == 0) {
                    return "";
                } // if
                return ((AssemblyProductAttribute)attributes[0]).Product;
            } // get
        } // AssemblyProduct

        // Авторские права
        public string AssemblyCopyright {
            get {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCopyrightAttribute), false);
                if (attributes.Length == 0) {
                    return "";
                } // if
                return ((AssemblyCopyrightAttribute)attributes[0]).Copyright;
            } // get
        } // AssemblyCopyright

        // Организация
        public string AssemblyCompany {
            get {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCompanyAttribute), false);
                if (attributes.Length == 0) {
                    return "";
                } // if
                return ((AssemblyCompanyAttribute)attributes[0]).Company;
            } // get
        } // AssemblyCompany
        #endregion


        private void AboutWindow_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Close();
        } // AboutWindow_MouseLeftButtonDown
    } // class AboutWindow : Window
} // namespace WPF_Template.Windows
