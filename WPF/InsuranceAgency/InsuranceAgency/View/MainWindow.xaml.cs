/*==========================================================
** 
** Логика взаимодействия для MainWindow.xaml
** 
** Copyright(c) Alexey Bur'yanov, 2017
** <OWNER>Alexey Bur'yanov</OWNER>
** 
===========================================================*/

using System.Windows;
using InsuranceAgency.LINQtoSQL;

namespace InsuranceAgency
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private InsuranceContractsABDataContext _db;

        public MainWindow()
        {
            InitializeComponent();

            _db = new InsuranceContractsABDataContext();

            // Так спокойней, ибо был случай вылета приложения по выходу
            Closing += (s, e) => {
                _db.Connection.Close();
                _db.Connection.Dispose();
                _db.Dispose();
            };

            try {
                // Привязка БД к таблицам и её комбо-боксам (второстепенным табличкам)
                BindingContracts();
                BindingCanceledContracts();
                BindingTypesInsurance();
                // Товарищей клиентов и агентов привязываем во ViewModel для пущего удобства использования DataSet'ов
                //BindingClientage();
                //BindingAgents();
            } catch (System.Data.SqlClient.SqlException e) {
                System.Windows.Forms.MessageBox.Show($"Сервер {e.Server} выключен или недоступен." +
                    $"\n{e.Message}\nСерьёзность: {e.Class}\nТип ошибки:{e.Number}", "Ошибка подключения к базе данных",
                    System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Exclamation);
            } // try-catch

            DataContext = new ApplicationViewModel(_db, this, new DefaultDialogService());
        } // MainWindow

        public void BindingContracts()
        {
            dataGridContracts.ItemsSource    = _db.Contracts.GetNewBindingList(); // создаём новый список для привязки к источнику 
            ComboClients.ItemsSource         = _db.Clientage.GetNewBindingList();
            ComboAgents.ItemsSource          = _db.Agents.GetNewBindingList();
            ComboTypeInsurance.ItemsSource   = _db.TypesInsurance.GetNewBindingList();
        } // BindingContracts

        public void BindingCanceledContracts()
        {
            dataGridCanceledContracts.ItemsSource = _db.CanceledContracts.GetNewBindingList();
            ComboClientsCanc.ItemsSource          = _db.Clientage.GetNewBindingList();
            ComboAgentsCanc.ItemsSource           = _db.Agents.GetNewBindingList();
            ComboTypeInsuranceCanc.ItemsSource    = _db.TypesInsurance.GetNewBindingList();
        } // BindingCanceledContracts

        public void BindingTypesInsurance()
        {
            dataGridTypesInsurance.ItemsSource = _db.TypesInsurance.GetNewBindingList();
        } // BindingTypesInsurance

        public void BindingClientage()
        {
            // Вариант №2
            // Через дата-сэт
            // DefaultView содержит фильтры в том числе 
            // и для отображения картинок с БД без всяких преобразований, что очень удобно
            //using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
            //    connection.Open();
            //    SqlDataAdapter adapter = new SqlDataAdapter(sql, connection);
            //    DataSet ds = new DataSet();
            //    adapter.Fill(ds);
            //    dataGridClientage.ItemsSource = ds.Tables[0].DefaultView;
            //} // using

            // Вариант №1. Его проблема: 
            //             нет связи с БД, потому не можем теперь легко сабмитить изменения, но зато отображается фото
            // Добавляем столбцы в дата-грид ----------------------------------------------------------------------------
            // если их нет
            // ИД
            //if (dataGridClientage.Columns.Count == 0) {
            //    dataGridClientage.Columns.Add(new DataGridTextColumn() {
            //        Header = "ИД",
            //        Binding = new Binding("Id"),
            //        Width = 40,
            //        IsReadOnly = true
            //    });
            //    // ФАМИЛИЯ
            //    dataGridClientage.Columns.Add(new DataGridTextColumn() {
            //        Header = "Фамилия",
            //        Binding = new Binding("SecondName"),
            //        Width = 100
            //    });
            //    // ИМЯ
            //    dataGridClientage.Columns.Add(new DataGridTextColumn() {
            //        Header = "Имя",
            //        Binding = new Binding("FirstName"),
            //        Width = 100
            //    });
            //    // ОТЧЕСТВО
            //    dataGridClientage.Columns.Add(new DataGridTextColumn() {
            //        Header = "Отчество",
            //        Binding = new Binding("MiddleName"),
            //        Width = 100
            //    });
            //    // ПАСПОРТ
            //    dataGridClientage.Columns.Add(new DataGridTextColumn() {
            //        Header = "Паспорт",
            //        Binding = new Binding("Passport"),
            //        Width = 100
            //    });
            //    // СКИДКА
            //    dataGridClientage.Columns.Add(new DataGridTextColumn() {
            //        Header = "Скидка (%)",
            //        Binding = new Binding("Discount"),
            //        Width = 75
            //    });
            //    // ФОТО КЛИЕНТА
            //    // Создаём шаблон
            //    FrameworkElementFactory factory = new FrameworkElementFactory(typeof(System.Windows.Controls.Image));
            //    // Привязка
            //    Binding bind = new Binding("Photo");
            //    // Привязка соответствует св-ву зависимостей Image
            //    factory.SetValue(System.Windows.Controls.Image.SourceProperty, bind);
            //    // DataTemplate ячейки соответствует нашему шаблону
            //    DataTemplate cellTemplate = new DataTemplate() { VisualTree = factory };
            //    // Настраиваем столбец
            //    DataGridTemplateColumn imgCol = new DataGridTemplateColumn() {
            //        Header = "Фото клиента",
            //        CellTemplate = cellTemplate,
            //        Width = 100,
            //        IsReadOnly = true
            //    };
            //    // Добавляем настроенный столбец
            //    dataGridClientage.Columns.Add(imgCol);
            //} // if
            //// ----------------------------------------------------------------------------------------------------------

            //// Список, который в последствии заполнения будем присваивать в ItemSource
            //ObservableCollection<Client> clientList = new ObservableCollection<Client>();

            //// Проходим по клиентам, выбираем данные и конвертируем фото
            //foreach (var dbClient in _db.Clientage) {
            //    clientList.Add(new Client() {
            //        Id         = dbClient.Id,
            //        SecondName = dbClient.CSecondName,
            //        FirstName  = dbClient.CFirstName,
            //        MiddleName = dbClient.CMiddleName,
            //        Passport   = dbClient.CPassport,
            //        Discount   = dbClient.CDiscount,
            //        Photo      = Service.Utils.ToBitmap(dbClient.CPhoto.ToArray())
            //    });
            //} // foreach

            //dataGridClientage.ItemsSource = clientList;
        } // BindingClientage

        public void BindingAgents()
        {
            // Вариант №2
            // Через дата-сэт
            // DefaultView содержит фильтры в том числе и для отображения картинок с БД без всяких преобразований
            //using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
            //    connection.Open();
            //    string sql = "SELECT * FROM Agents";
            //    SqlDataAdapter adapter = new SqlDataAdapter(sql, connection);

            //    DataSet ds = new DataSet();
            //    adapter.Fill(ds);
            //    dataGridAgents.ItemsSource = ds.Tables[0].DefaultView;
            //} // using

            // Вариант №1. Его проблема: 
            //             нет связи с БД, потому не можем теперь легко сабмитить изменения, но зато отображается фото
            // Добавляем столбцы в дата-грид агентов -------------------------------------------------------------------
            // ИД
            //if (dataGridAgents.Columns.Count == 0) {
            //    dataGridAgents.Columns.Add(new DataGridTextColumn() {
            //        Header = "ИД",
            //        Binding = new Binding("Id"),
            //        Width = 40,
            //        IsReadOnly = true
            //    });
            //    // ФАМИЛИЯ
            //    dataGridAgents.Columns.Add(new DataGridTextColumn() {
            //        Header = "Фамилия",
            //        Binding = new Binding("SecondName"),
            //        Width = 100
            //    });
            //    // ИМЯ
            //    dataGridAgents.Columns.Add(new DataGridTextColumn() {
            //        Header = "Имя",
            //        Binding = new Binding("FirstName"),
            //        Width = 100
            //    });
            //    // ОТЧЕСТВО
            //    dataGridAgents.Columns.Add(new DataGridTextColumn() {
            //        Header = "Отчество",
            //        Binding = new Binding("MiddleName"),
            //        Width = 100
            //    });
            //    // НАГРАДА
            //    dataGridAgents.Columns.Add(new DataGridTextColumn() {
            //        Header = "Награда (%)",
            //        Binding = new Binding("Reward"),
            //        Width = 75
            //    });
            //    // ФОТО АГЕНТА
            //    // Создаём шаблон
            //    FrameworkElementFactory factory = new FrameworkElementFactory(typeof(System.Windows.Controls.Image));
            //    // Привязка
            //    Binding bind = new Binding("Photo");
            //    // Привязка соответствует св-ву зависимостей Image
            //    factory.SetValue(System.Windows.Controls.Image.SourceProperty, bind);
            //    // DataTemplate ячейки соответствует нашему шаблону
            //    DataTemplate cellTemplate = new DataTemplate() { VisualTree = factory };
            //    // Настраиваем столбец
            //    DataGridTemplateColumn imgCol = new DataGridTemplateColumn() {
            //        Header = "Фото агента",
            //        CellTemplate = cellTemplate,
            //        Width = 100,
            //        IsReadOnly = true
            //    };
            //    // Добавляем настроенный столбец
            //    dataGridAgents.Columns.Add(imgCol);
            //} // if
            //// ----------------------------------------------------------------------------------------------------------

            //// Список, который в последствии заполнения будем присваивать в ItemSource
            //ObservableCollection<Agent> clientList = new ObservableCollection<Agent>();

            //// Проходим по агентам, выбираем данные и конвертируем фото
            //foreach (var dbAgent in _db.Agents) {
            //    clientList.Add(new Agent() {
            //        Id         = dbAgent.Id,
            //        SecondName = dbAgent.ASecondName,
            //        FirstName  = dbAgent.AFirstName,
            //        MiddleName = dbAgent.AMiddleName,
            //        Reward     = dbAgent.AReward,
            //        Photo      = Service.Utils.ToBitmap(dbAgent.APhoto.ToArray())
            //    });
            //} // foreach

            //dataGridAgents.ItemsSource = clientList;
        } // BindingAgents
    } // class MainWindow
} // namespace InsuranceAgency