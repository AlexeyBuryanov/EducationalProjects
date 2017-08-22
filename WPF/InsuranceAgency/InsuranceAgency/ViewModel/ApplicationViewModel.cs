using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using InsuranceAgency.LINQtoSQL;
using InsuranceAgency.Service;
using InsuranceAgency.Windows;

namespace InsuranceAgency
{
    public class ApplicationViewModel : INotifyPropertyChanged
    {
        private InsuranceContractsABDataContext _db;
        private MainWindow _mainWindow;
        private DataGrid _dataGridContracts, _dataGridClientage, _dataGridAgents, 
                         _dataGridTypesInsurance, _dataGridOperations;
        private TextBlock _notifiOp;
        private TextBox _textBoxInputOp1, _textBoxInputOp2;
        private DataSet _dataSetClientage, _dataSetAgents;
        private SqlDataAdapter _adapterClientage, _adapterAgents;
        private SqlCommandBuilder _commandBuilder;
        private string selectClientage = "SELECT * FROM Clientage";
        private string selectAgents = "SELECT * FROM Agents";
        private IDialogService _dialogService;

        public ApplicationViewModel(InsuranceContractsABDataContext db, MainWindow mainWindow, 
            IDialogService dialogService)
        {
            _dialogService = dialogService;

            // БД
            _db = db;
            // Главное окно
            _mainWindow = mainWindow;

            // Получаем доступ к таблицам в главном окне
            _dataGridContracts       = (DataGrid)_mainWindow.FindName("dataGridContracts");
            _dataGridClientage       = (DataGrid)_mainWindow.FindName("dataGridClientage");
            _dataGridAgents          = (DataGrid)_mainWindow.FindName("dataGridAgents");
            _dataGridTypesInsurance  = (DataGrid)_mainWindow.FindName("dataGridTypesInsurance");

            // Операции ----
            _dataGridOperations = (DataGrid)_mainWindow.FindName("dataGridOperations");
            // TextBlock-уведомления
            _notifiOp = (TextBlock)_mainWindow.FindName("notifiOp");
            // Поля для ввода
            _textBoxInputOp1 = (TextBox)_mainWindow.FindName("textBoxInputOp1");
            _textBoxInputOp2 = (TextBox)_mainWindow.FindName("textBoxInputOp2");

            //***** СОЗДАНИЕ КОМАНД *****//
            ExitCommand                = new RelayCommand(Exit);
            MinimizeCommand            = new RelayCommand(Minimize);
            AboutCommand               = new RelayCommand(About);
            InsertClientCommand        = new RelayCommand(InsertClient);
            DeleteClientCommand        = new RelayCommand(DeleteClient);
            UpdateClientCommand        = new RelayCommand(UpdateClient);
            InsertAgentCommand         = new RelayCommand(InsertAgent);
            DeleteAgentCommand         = new RelayCommand(DeleteAgent);
            UpdateAgentCommand         = new RelayCommand(UpdateAgent);
            SubmitContractCommand      = new RelayCommand(SubmitContract);
            DeleteContractCommand      = new RelayCommand(DeleteContract);
            SubmitTypeInsuranceCommand = new RelayCommand(SubmitTypeInsurance);
            DeleteTypeInsuranceCommand = new RelayCommand(DeleteTypeInsurance);
            ChangePhotoClientCommand   = new RelayCommand(ChangePhotoClient);
            ChangePhotoAgentCommand    = new RelayCommand(ChangePhotoAgent);
            Request01Command           = new RelayCommand(Request01);
            Request02Command           = new RelayCommand(Request02);
            Request03Command           = new RelayCommand(Request03);
            Request04Command           = new RelayCommand(Request04);
            Request05Command           = new RelayCommand(Request05);
            Request06Command           = new RelayCommand(Request06);
            Request07Command           = new RelayCommand(Request07);
            Request08Command           = new RelayCommand(Request08);
            Request09Command           = new RelayCommand(Request09);
            Request10Command           = new RelayCommand(Request10);
            Request11Command           = new RelayCommand(Request11);
            Request12Command           = new RelayCommand(Request12);

            // Привязка через DataSet к клиентам и агентам
            ConnectToClientage();
            ConnectToAgents();

            StatusText = "Добро пожаловать";
        } // ApplicationViewModel

        private void ConnectToClientage()
        {
            using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
                connection.Open();
                string sql = "SELECT * FROM Clientage";
                _adapterClientage = new SqlDataAdapter(sql, connection);
                _dataSetClientage = new DataSet();
                _adapterClientage.Fill(_dataSetClientage);
                _dataGridClientage.ItemsSource = _dataSetClientage.Tables[0].DefaultView;
            } // using
        } // ConnectToClientage

        private void ConnectToAgents()
        {
            using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
                connection.Open();
                string sql = "SELECT * FROM Agents";
                _adapterAgents = new SqlDataAdapter(sql, connection);
                _dataSetAgents = new DataSet();
                _adapterAgents.Fill(_dataSetAgents);
                _dataGridAgents.ItemsSource = _dataSetAgents.Tables[0].DefaultView;
            } // using
        } // ConnectToAgents

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged([CallerMemberName]string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        } // OnPropertyChanged

        //******************** СВОЙСТВА ДЛЯ СВЯЗИ С ИНТЕРФЕЙСОМ ***********************//

        // Текстовка в статус-баре
        private string _statusText;
        public string StatusText {
            get { return _statusText; }
            private set {
                _statusText = value;
                OnPropertyChanged("StatusText");
            } // set
        } // StatusText

        //********************************* КОМАНДЫ ***********************************//

        // Выход
        private RelayCommand _exitCommand;
        public RelayCommand ExitCommand {
            get { return _exitCommand; }
            set { _exitCommand = value; }
        } // ExitCommand

        // Свернуть
        private RelayCommand _minimizeCommand;
        public RelayCommand MinimizeCommand {
            get { return _minimizeCommand; }
            set { _minimizeCommand = value; }
        } // MinimizeCommand

        // О программе
        private RelayCommand _aboutCommand;
        public RelayCommand AboutCommand {
            get { return _aboutCommand; }
            set { _aboutCommand = value; }
        } // AboutCommand

        // buttonInsertClient
        private RelayCommand _insertClientCommand;
        public RelayCommand InsertClientCommand {
            get { return _insertClientCommand; }
            set { _insertClientCommand = value; }
        } // InsertClientCommand

        // buttonDeleteClient
        private RelayCommand _deleteClientCommand;
        public RelayCommand DeleteClientCommand {
            get { return _deleteClientCommand; }
            set { _deleteClientCommand = value; }
        } // DeleteClientCommand

        // buttonUpdateClient
        private RelayCommand _updateClientCommand;
        public RelayCommand UpdateClientCommand {
            get { return _updateClientCommand; }
            set { _updateClientCommand = value; }
        } // UpdateClientCommand

        // buttonSubmitContract
        private RelayCommand _submitContractCommand;
        public RelayCommand SubmitContractCommand {
            get { return _submitContractCommand; }
            set { _submitContractCommand = value; }
        } // SubmitContractCommand

        // buttonDeleteContract
        private RelayCommand _deleteContractCommand;
        public RelayCommand DeleteContractCommand {
            get { return _deleteContractCommand; }
            set { _deleteContractCommand = value; }
        } // DeleteContractCommand

        // buttonInsertAgent
        private RelayCommand _insertAgentCommand;
        public RelayCommand InsertAgentCommand {
            get { return _insertAgentCommand; }
            set { _insertAgentCommand = value; }
        } // InsertAgentCommand

        // buttonDeleteAgent
        private RelayCommand _deleteAgentCommand;
        public RelayCommand DeleteAgentCommand {
            get { return _deleteAgentCommand; }
            set { _deleteAgentCommand = value; }
        } // DeleteAgentCommand

        // buttonUpdateAgent
        private RelayCommand _updateAgentCommand;
        public RelayCommand UpdateAgentCommand {
            get { return _updateAgentCommand; }
            set { _updateAgentCommand = value; }
        } // UpdateAgentCommand

        // buttonSubmitTypeInsurance
        private RelayCommand _submitTypeInsuranceCommand;
        public RelayCommand SubmitTypeInsuranceCommand {
            get { return _submitTypeInsuranceCommand; }
            set { _submitTypeInsuranceCommand = value; }
        } // SubmitTypeInsuranceCommand

        // buttonDeleteTypeInsurance
        private RelayCommand _deleteTypeInsuranceCommand;
        public RelayCommand DeleteTypeInsuranceCommand {
            get { return _deleteTypeInsuranceCommand; }
            set { _deleteTypeInsuranceCommand = value; }
        } // DeleteTypeInsuranceCommand

        // buttonChangePhotoClient
        private RelayCommand _changePhotoClientCommand;
        public RelayCommand ChangePhotoClientCommand {
            get { return _changePhotoClientCommand; }
            set { _changePhotoClientCommand = value; }
        } // ChangePhotoClientCommand

        // buttonChangePhotoAgent
        private RelayCommand _changePhotoAgentCommand;
        public RelayCommand ChangePhotoAgentCommand {
            get { return _changePhotoAgentCommand; }
            set { _changePhotoAgentCommand = value; }
        } // ChangePhotoAgentCommand

        // Запрос 01
        private RelayCommand _request01Command;
        public RelayCommand Request01Command {
            get { return _request01Command; }
            set { _request01Command = value; }
        } // Request01Command

        // Запрос 02
        private RelayCommand _request02Command;
        public RelayCommand Request02Command {
            get { return _request02Command; }
            set { _request02Command = value; }
        } // Request02Command

        // Запрос 03
        private RelayCommand _request03Command;
        public RelayCommand Request03Command {
            get { return _request03Command; }
            set { _request03Command = value; }
        } // Request03Command

        // Запрос 04
        private RelayCommand _request04Command;
        public RelayCommand Request04Command {
            get { return _request04Command; }
            set { _request04Command = value; }
        } // Request04Command

        // Запрос 05
        private RelayCommand _request05Command;
        public RelayCommand Request05Command {
            get { return _request05Command; }
            set { _request05Command = value; }
        } // Request05Command

        // Запрос 06
        private RelayCommand _request06Command;
        public RelayCommand Request06Command {
            get { return _request06Command; }
            set { _request06Command = value; }
        } // Request06Command

        // Запрос 07
        private RelayCommand _request07Command;
        public RelayCommand Request07Command {
            get { return _request07Command; }
            set { _request07Command = value; }
        } // Request07Command

        // Запрос 08
        private RelayCommand _request08Command;
        public RelayCommand Request08Command {
            get { return _request08Command; }
            set { _request08Command = value; }
        } // Request08Command

        // Запрос 09
        private RelayCommand _request09Command;
        public RelayCommand Request09Command {
            get { return _request09Command; }
            set { _request09Command = value; }
        } // Request09Command

        // Запрос 10
        private RelayCommand _request10Command;
        public RelayCommand Request10Command {
            get { return _request10Command; }
            set { _request10Command = value; }
        } // Request10Command

        // Запрос 11
        private RelayCommand _request11Command;
        public RelayCommand Request11Command {
            get { return _request11Command; }
            set { _request11Command = value; }
        } // Request11Command

        // Запрос 12
        private RelayCommand _request12Command;
        public RelayCommand Request12Command {
            get { return _request12Command; }
            set { _request12Command = value; }
        } // Request12Command

        //**************************** РЕАЛИЗАЦИИ КОМАНД ******************************//

        // Выход
        private void Exit(object obj)
        {
            Application.Current.Shutdown();
        } // Exit

        // Свернуть
        private void Minimize(object obj)
        {
            Application.Current.MainWindow.WindowState = WindowState.Minimized;
        } // Exit

        // О программе
        private void About(object obj)
        {
            AboutWindow win = new AboutWindow(Application.Current.MainWindow);
            win.ShowDialog();
        } // About

        // buttonInsertClient
        private void InsertClient(object obj)
        {
            try {
                // Добавляем новую строку в DataTable
                // Автоматически формируется новая строка и в DataGrid т.к. ранее было всё связано
                DataRow row = _dataSetClientage.Tables[0].NewRow();
                _dataSetClientage.Tables[0].Rows.Add(row);

                _dataGridClientage.SelectedIndex = _dataGridClientage.Items.Count-1;

                StatusText = "Новая строка добавлена. Отредактируйте и нажмите \"Сохранить\" для подтверждения";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при добавлении нового клиента...";
            } // try-catch
        } // SubmitClient

        // buttonDeleteClient
        private void DeleteClient(object obj)
        {
            try {
                // Уход, если ничего не выбрано
                if (_dataGridClientage.SelectedItems.Count == 0) return;

                DataRowView drv = (DataRowView)_dataGridClientage.SelectedItem;

                if (drv.IsNew || drv.IsEdit) {
                    System.Windows.Forms.DialogResult ds =
                    System.Windows.Forms.MessageBox.Show("Данная строка является новой или находится в режиме редактирования.\nХотите удалить?", "Действие со строкой",
                        System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Error);
                    if (ds == System.Windows.Forms.DialogResult.Yes) {
                        drv.Row.EndEdit();
                        drv.Row.Delete();
                    } // if
                } else {
                    drv.Row.Delete();
                } // if

                // Вариант №1
                //if (_dataGridClientage.SelectedItem is Client w) {
                //    // Находим нужного клиента через LINQ-запрос
                //    Clientage clientdb = 
                //     _db.Clientage
                //        .Where(item => 
                //            item.Id          == w.Id         &&
                //            item.CSecondName == w.SecondName &&
                //            item.CFirstName  == w.FirstName  &&
                //            item.CMiddleName == w.MiddleName &&
                //            item.CPassport   == w.Passport   &&
                //            item.CDiscount   == w.Discount)
                //        .FirstOrDefault();

                //    // Удаляем
                //    _db.Clientage.DeleteOnSubmit(clientdb);
                //} // if

                //_db.SubmitChanges();

                //// Обновить привязку клиентов
                //_mainWindow.BindingClientage();
                //// И привязку договоров, чтобы обновить информацию в комбо-боксах
                //_mainWindow.BindingContracts();

                StatusText = "Успешно удалено. Чтобы подтвердить действие нажмите кнопку \"Сохранить\"";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при удалении клиента...";
            } // try-catch
        } // DeleteClient

        // buttonUpdateClient
        private void UpdateClient(object obj)
        {
            try {
                using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
                    connection.Open();
                    _adapterClientage = new SqlDataAdapter(selectClientage, connection);
                    _commandBuilder = new SqlCommandBuilder(_adapterClientage);
                    _adapterClientage.InsertCommand = new SqlCommand("sp_CreateClient", connection) {
                        CommandType = CommandType.StoredProcedure
                    };
                    SqlParameter parameter = _adapterClientage.InsertCommand.Parameters.Add("@id", SqlDbType.Int, 0, "Id");
                    parameter.Direction = ParameterDirection.Output;
                    _adapterClientage.InsertCommand.Parameters.Add(new SqlParameter("@secondName", SqlDbType.NVarChar, 60, "CSecondName"));
                    _adapterClientage.InsertCommand.Parameters.Add(new SqlParameter("@firstName",  SqlDbType.NVarChar, 60, "CFirstName"));
                    _adapterClientage.InsertCommand.Parameters.Add(new SqlParameter("@middleName", SqlDbType.NVarChar, 60, "CMiddleName"));
                    _adapterClientage.InsertCommand.Parameters.Add(new SqlParameter("@passport",   SqlDbType.NVarChar, 10, "CPassport"));
                    _adapterClientage.InsertCommand.Parameters.Add(new SqlParameter("@discount",   SqlDbType.Float,     0, "CDiscount"));
                    _adapterClientage.InsertCommand.Parameters.Add(new SqlParameter("@photo",      SqlDbType.Image,     0, "CPhoto"));
                    _adapterClientage.Update(_dataSetClientage);
                } // using

                // Обновляем контракты, чтобы в комбо-боксах содержалась актуальная информация
                _mainWindow.BindingContracts();
                StatusText = "Сохранено успешно";
            } catch (SqlException) {
                StatusText = "Сохранить пустые строки невозможно! Пожалуйста, введите нужные данные...";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка в подтверждении данных клиентов...";
            } // try-catch
        } // UpdateClient

        // buttonInsertAgent
        private void InsertAgent(object obj)
        {
            try {
                DataRow row = _dataSetAgents.Tables[0].NewRow();
                _dataSetAgents.Tables[0].Rows.Add(row);

                _dataGridAgents.SelectedIndex = _dataGridAgents.Items.Count - 1;

                StatusText = "Новая строка добавлена. Отредактируйте и нажмите \"Сохранить\" для подтверждения";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при добавлении нового агента...";
            } // try-catch
        } // InsertAgent

        // buttonDeleteAgent
        private void DeleteAgent(object obj)
        {
            try {
                // Уход, если ничего не выбрано
                if (_dataGridAgents.SelectedItems.Count == 0) return;

                DataRowView drv = (DataRowView)_dataGridAgents.SelectedItem;

                if (drv.IsNew || drv.IsEdit) {
                    System.Windows.Forms.DialogResult ds =
                    System.Windows.Forms.MessageBox.Show("Данная строка является новой или находится в режиме редактирования.\nХотите удалить?", "Действие со строкой",
                        System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Error);
                    if (ds == System.Windows.Forms.DialogResult.Yes) {
                        drv.Row.EndEdit();
                        drv.Row.Delete();
                    } // if
                } else {
                    drv.Row.Delete();
                } // if

                StatusText = "Успешно удалено. Чтобы подтвердить действие нажмите кнопку \"Сохранить\"";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при удалении агента...";
            } // try-catch
        } // DeleteAgent

        // buttonUpdateAgent
        private void UpdateAgent(object obj)
        {
            try {
                using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
                    connection.Open();
                    _adapterAgents = new SqlDataAdapter(selectAgents, connection);
                    _commandBuilder = new SqlCommandBuilder(_adapterAgents);
                    _adapterAgents.InsertCommand = new SqlCommand("sp_CreateAgent", connection) {
                        CommandType = CommandType.StoredProcedure
                    };
                    SqlParameter parameter = _adapterAgents.InsertCommand.Parameters.Add("@id", SqlDbType.Int, 0, "Id");
                    parameter.Direction = ParameterDirection.Output;
                    _adapterAgents.InsertCommand.Parameters.Add(new SqlParameter("@secondName", SqlDbType.NVarChar, 60, "ASecondName"));
                    _adapterAgents.InsertCommand.Parameters.Add(new SqlParameter("@firstName",  SqlDbType.NVarChar, 60, "AFirstName"));
                    _adapterAgents.InsertCommand.Parameters.Add(new SqlParameter("@middleName", SqlDbType.NVarChar, 60, "AMiddleName"));
                    _adapterAgents.InsertCommand.Parameters.Add(new SqlParameter("@reward",     SqlDbType.Float, 0,     "AReward"));
                    _adapterAgents.InsertCommand.Parameters.Add(new SqlParameter("@photo",      SqlDbType.Image, 0,     "APhoto"));
                    _adapterAgents.Update(_dataSetAgents);
                } // using

                // Обновляем контракты, чтобы в комбо-боксах содержалась актуальная информация
                _mainWindow.BindingContracts();

                StatusText = "Сохранено успешно";
            } catch (SqlException) {
                StatusText = "Сохранить пустые строки невозможно! Пожалуйста, введите нужные данные...";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка в подтверждении данных агентов...";
            } // try-catch
        } // UpdateAgent

        // buttonSubmitContract
        private void SubmitContract(object obj)
        {
            try {
                _db.SubmitChanges();

                _mainWindow.BindingContracts();

                StatusText = "Изменения применены";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка в подтверждении данных договоров...";
            } // try-catch
        } // SubmitContract

        // buttonDeleteContract
        private void DeleteContract(object obj)
        {
            try {
                if (_dataGridContracts.SelectedItems.Count == 0) return;

                System.Windows.Forms.DialogResult ds =
                System.Windows.Forms.MessageBox.Show("Данная операция необратима. Подтвердить?", "Удаление договора",
                    System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Exclamation);

                if (ds == System.Windows.Forms.DialogResult.Yes) {
                    // Через запрос копируем удаляемую строку в таблицу отменённых договоров
                    // TODO: Вывести окно с TextBox'ом для ввода причины расторжения
                    CanceledContractsInto(_dataGridContracts.SelectedItem as Contracts, "тест");

                    _db.Contracts.DeleteOnSubmit(_dataGridContracts.SelectedItem as Contracts);

                    _db.SubmitChanges();

                    _mainWindow.BindingContracts();
                    _mainWindow.BindingCanceledContracts();

                    StatusText = "Успешно удалено. Данный договор помещён в таблицу \"Расторгнутые договора\"";
                } // if
            } catch (System.Data.SqlTypes.SqlTypeException) {
                StatusText = "Ошибка! Некорректные значения, столбцов.";
                System.Windows.Forms.MessageBox.Show($"Убедитесь, что дата введена правильно, а сумма не меньше нуля.", "Ошибка",
                    System.Windows.Forms.MessageBoxButtons.OKCancel, System.Windows.Forms.MessageBoxIcon.Error);
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при удалении договоров...";
            } // try-catch
        } // DeleteContract
        private void CanceledContractsInto(Contracts contracts, string terminationSign)
        {
            string query = @"
                INSERT INTO CanceledContracts (IdClient, IdAgent, IdTypeInsurance, SumInsurance, DateConclusion, TerminationSign) VALUES
                    ({0}, {1}, {2}, {3:n2}, {4:yyyy.MM.dd}, {5})";

            _db.ExecuteCommand(query, contracts.IdClient, contracts.IdAgent, contracts.IdTypeInsurance, contracts.SumInsurance,
                    contracts.DateConclusion, terminationSign);
        } // CanceledContractsInto

        // buttonSubmitTypeInsurance
        private void SubmitTypeInsurance(object obj)
        {
            try {
                _db.SubmitChanges();

                _mainWindow.BindingTypesInsurance();
                _mainWindow.BindingContracts();

                StatusText = "Изменения применены";
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка в подтверждении данных видов страхований...";
            } // try-catch
        } // SubmitTypeInsurance

        // buttonDeleteTypeInsurance
        private void DeleteTypeInsurance(object obj)
        {
            try {
                if (_dataGridTypesInsurance.SelectedItems.Count == 0) return;

                System.Windows.Forms.DialogResult ds =
                System.Windows.Forms.MessageBox.Show("Данная операция необратима. Подтвердить?", "Удаление выбранных агентов",
                    System.Windows.Forms.MessageBoxButtons.YesNo, System.Windows.Forms.MessageBoxIcon.Exclamation);

                if (ds == System.Windows.Forms.DialogResult.Yes) {
                    foreach (object t in _dataGridTypesInsurance.SelectedItems) {
                        if (t is TypesInsurance w)
                            _db.TypesInsurance.DeleteOnSubmit(w);
                    } // foreach

                    _db.SubmitChanges();

                    _mainWindow.BindingTypesInsurance();
                    _mainWindow.BindingContracts();

                    StatusText = "Успешно удалено";
                } // if
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при удалении агентов...";
            } // try-catch
        } // DeleteTypeInsurance

        // buttonChangePhotoClient
        private void ChangePhotoClient(object obj)
        {
            try {
                if (_dataGridClientage.SelectedItems.Count == 0) {
                    StatusText = "Выберите клиента кому хотите изменить фото...";
                    return;
                } // if

                // Выбранный клиент
                Clientage selected = new Clientage();
                // Все клиенты для перебора по циклу (как по другому можно сделать не знаю)
                List<Clientage> clientage = new List<Clientage>();
                // "Экспортируем" клиентов в наш список для дальнейшей индексации по выбранному индексу
                // Так мы получаем того клиента, которого хотим модернизировать новым фото
                foreach (var item in _db.Clientage) {
                    clientage.Add(item);
                } // foreach
                // DataRowView выбранного итема
                DataRowView drv = (DataRowView)_dataGridClientage.SelectedItem;
                // Если это новая строка, значит нужно отсюда уходить
                // ибо индекс выбранного будет за пределами того, что мы имеем в базе.
                // Нужно сначала синхронизировать базу, чтобы знать о новой строке.
                // Потом только делать апдейт фото. В этом минус сего алгоритма
                // т.к. здесь мы работаем и с классами LINQ to SQL, и с DataSet
                if (clientage.Count != drv.Row.Table.Rows.Count) {
                    StatusText = "Извините, но фото данного клиента сейчас изменить нельзя. Нажмите \"Сохранить\"";
                    return;
                } // if

                if (_dialogService.OpenFileDialog() == true) {
                    // Получили байты
                    byte[] photoBytes = Utils.GetPhoto(_dialogService.FilePath);

                    // Создаём подключение для выполнения команды
                    using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
                        connection.Open();
                        // Тот самый цикл
                        for (int i = 0; i < drv.Row.Table.Rows.Count; i++) {
                            // Получаем того самого
                            selected = clientage[_dataGridClientage.SelectedIndex];
                        } // for

                        // Формируем команду на апдейт
                        SqlCommand command = new SqlCommand(
                        "UPDATE Clientage              " +
                        "   SET CPhoto = @PhotoBytes   " +
                        "  FROM Clientage              " +
                        " WHERE Id    = @SelectedUserId"
                        , connection);
                        // Параметры для смена фото
                        command.Parameters.Add("@PhotoBytes", SqlDbType.Image, photoBytes.Length).Value = photoBytes;
                        // Где фото - наш выбранный пассажир
                        command.Parameters.Add("@SelectedUserId", SqlDbType.Int, 0).Value = selected.Id;

                        // Выполняем
                        command.ExecuteNonQuery();
                        // Коннектимся для синхронизации
                        ConnectToClientage();
                    } // using
                    StatusText = "Фото клиента успешно изменено. Сохранять не требуется";
                } // if
            } catch (SqlException e) {
                StatusText = "Ошибка связанная с сервером...";
                _dialogService.ShowError(e.Message);
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при изменении фото клиента...";
            } // try-catch
        } // ChangePhotoClient

        // buttonChangePhotoAgent
        private void ChangePhotoAgent(object obj)
        {
            try {
                if (_dataGridAgents.SelectedItems.Count == 0) {
                    StatusText = "Выберите агента кому хотите изменить фото...";
                    return;
                } // if

                // Выбранный агент
                Agents selected = new Agents();
                // Все агенты для перебора по циклу (как по другому можно сделать не знаю)
                List<Agents> agents = new List<Agents>();
                // "Экспортируем" агентов в наш список для дальнейшей индексации по выбранному индексу
                // Так мы получаем того клиента, которого хотим модернизировать новым фото
                foreach (var item in _db.Agents) {
                    agents.Add(item);
                } // foreach
                // DataRowView выбранного итема
                DataRowView drv = (DataRowView)_dataGridAgents.SelectedItem;
                // Если это новая строка, значит нужно отсюда уходить
                // ибо индекс выбранного будет за пределами того, что мы имеем в базе.
                // Нужно сначала синхронизировать базу, чтобы знать о новой строке.
                // Потом только делать апдейт фото. В этом минус сего алгоритма
                // т.к. здесь мы работаем и с классами LINQ to SQL, и с DataSet
                if (agents.Count != drv.Row.Table.Rows.Count) {
                    StatusText = "Извините, но фото данного агента сейчас изменить нельзя. Нажмите \"Сохранить\"";
                    return;
                } // if

                if (_dialogService.OpenFileDialog() == true) {
                    // Получили байты
                    byte[] photoBytes = Utils.GetPhoto(_dialogService.FilePath);

                    using (SqlConnection connection = new SqlConnection(_db.Connection.ConnectionString)) {
                        connection.Open();
                        // Тот самый цикл
                        for (int i = 0; i < drv.Row.Table.Rows.Count; i++) {
                            // Получаем того самого
                            selected = agents[_dataGridAgents.SelectedIndex];
                        } // for

                        // Формируем команду на апдейт
                        SqlCommand command = new SqlCommand(
                        "UPDATE Agents                 " +
                        "   SET APhoto = @PhotoBytes   " +
                        "  FROM Agents                 " +
                        " WHERE Id    = @SelectedUserId"
                        , connection);
                        // Параметры для смена фото
                        command.Parameters.Add("@PhotoBytes", SqlDbType.Image, photoBytes.Length).Value = photoBytes;
                        // Где фото - наш выбранный пассажир
                        command.Parameters.Add("@SelectedUserId", SqlDbType.Int, 0).Value = selected.Id;

                        // Выполняем
                        command.ExecuteNonQuery();
                        // Коннектимся для синхронизации
                        ConnectToAgents();
                    } // using
                    StatusText = "Фото агента успешно изменено. Сохранять не требуется";
                } // if
            } catch (SqlException e) {
                StatusText = "Ошибка связанная с сервером...";
                _dialogService.ShowError(e.Message);
            } catch (Exception e) {
                _dialogService.ShowError(e.Message);
                StatusText = "Ошибка при изменении фото агента...";
            } // try-catch
        } // ChangePhotoAgent

        //********************************* ЗАПРОСЫ ***********************************//
        // Запрос 01
        // Выбирает из таблицы КЛИЕНТЫ информацию о клиентах, для которых процент скидки равен 0.5 %
        private void Request01(object obj)
        {
            // Скрываем все текст-боксы, чтобы не было неожиданностей
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            // Скрываем уведомление
            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            // ВАРИАНТ С РАБОЧИМ ФОТО ----------------------------------------------------------
            // Формируем нужные нам столбцы программно
            //Utils.AddColumn(_dataGridOperations, "ИД", 40, "Id", true);
            //Utils.AddColumn(_dataGridOperations, "Фамилия", 100, "SecondName");
            //Utils.AddColumn(_dataGridOperations, "Имя", 100, "FirstName");
            //Utils.AddColumn(_dataGridOperations, "Отчество", 100, "MiddleName");
            //Utils.AddColumn(_dataGridOperations, "Паспорт", 100, "Passport");
            //Utils.AddColumn(_dataGridOperations, "Скидка (%)", 100, "Discount");
            //Utils.AddColumn(_dataGridOperations, "Фото клиента", 100, "Photo", false, true);

            //// Список "модельных" клиентов для нормального отображения фото
            //ObservableCollection<Client> clientList = new ObservableCollection<Client>();

            //// _db.sp_Request01() - хранимая процедура
            //foreach (var dbClient in _db.sp_Request01().AsParallel().ToList()) {
            //    clientList.Add(new Client() {
            //        Id         = dbClient.Id,
            //        SecondName = dbClient.CSecondName,
            //        FirstName  = dbClient.CFirstName,
            //        MiddleName = dbClient.CMiddleName,
            //        Passport   = dbClient.CPassport,
            //        Discount   = dbClient.CDiscount,
            //        Photo      = Utils.ToBitmap(dbClient.CPhoto.ToArray())
            //    });
            //} // foreach

            //_dataGridOperations.ItemsSource = clientList;

            // ПЕРВЫЙ "ГРЯЗНЫЙ" ВАРИАНТ ------------------------------------------------------
            // В разметке указаны все столбы, которые нам могут понадобиться.
            // Дабы показывать в нужный момент только то, что нам нужно, используем св-во Visibility.
            // Только так я смог обойти проблему с созданием и привязкой столбцов программно...
            // Ибо программно создавать и привязывать столбцы уж слишком муторно здесь будет..
            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "ИД"               ||
                    (string)item.Header == "Фамилия клиента"  ||
                    (string)item.Header == "Имя клиента"      ||
                    (string)item.Header == "Отчество клиента" ||
                    (string)item.Header == "Паспорт клиента"  ||
                    (string)item.Header == "Скидка (%)"       ||
                    (string)item.Header == "Фото клиента")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            // Непосредственно исполнение самой хранимой процедуры
            _dataGridOperations.ItemsSource = _db.sp_Request01().AsParallel().ToList();

            // Показываем таблицу
            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 01 успешно выполнен";
        } // Request01

        // Запрос 02
        // Выбирает из таблицы АГЕНТЫ, ДОГОВОРЫ, КЛИЕНТЫ информацию о страховых агентах и клиентах, 
        // заключивших договора о страховании автомобиля
        private void Request02(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            // Скорей всего есть более простой и правильный способ, но на момент написания этой программы я о нём не знал
            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "Дата заключения договора" ||
                    (string)item.Header == "Сумма страхования"        ||
                    (string)item.Header == "Вид страхования"          ||
                    (string)item.Header == "Тариф"                    ||
                    (string)item.Header == "Ф.И.О. клиента"           ||
                    (string)item.Header == "Паспорт клиента"          ||
                    (string)item.Header == "Скидка (%)"               ||
                    (string)item.Header == "Ф.И.О. агента"            ||
                    (string)item.Header == "Награда (%)"              ||
                    (string)item.Header == "Фото клиента"             ||
                    (string)item.Header == "Фото агента")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request02().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 02 успешно выполнен";
        } // Request02

        // Запрос 03
        // Выбирает из таблиц КЛИЕНТЫ и ДОГОВОРЫ информацию о клиентах, заключивших договоры на 
        // сумму не меньше чем на 100 000 руб.
        private void Request03(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "Фамилия клиента"          ||
                    (string)item.Header == "Имя клиента"              ||
                    (string)item.Header == "Отчество клиента"         ||
                    (string)item.Header == "Паспорт клиента"          ||
                    (string)item.Header == "Скидка (%)"               ||
                    (string)item.Header == "Фото клиента"             ||
                    (string)item.Header == "Сумма страхования"        ||
                    (string)item.Header == "Дата заключения договора")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request03().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 03 успешно выполнен";
        } // Request03

        // Запрос 04
        // Выбирает из таблицы КЛИЕНТЫ информацию о клиентах с заданной фамилией. 
        // Фамилия вводится при выполнении запроса(в разработанном приложении)
        private void Request04(object obj)
        {
            // Скрываем таблицу
            _dataGridOperations.Visibility = Visibility.Collapsed;

            // Скрываем все столбцы, чтобы не мешались при вводе
            foreach (var item in _dataGridOperations.Columns) {
                item.Visibility = Visibility.Hidden;
            } // foreach

            // Подсказка
            _notifiOp.Visibility = Visibility.Visible;
            _notifiOp.Text = "Введите фамилию: ";

            // Активируем ввод
            _textBoxInputOp1.Text = "";
            _textBoxInputOp1.Visibility = Visibility.Visible;
            _textBoxInputOp1.Focus();
            _textBoxInputOp2.Visibility = Visibility.Hidden;
            StatusText = "ENTER - чтобы подтвердить ввод";

            try {
                // Событие для ввода значений по клавише Enter во вкладке операций
                // И уже стандартная низкоуровневая оптимизация...
                _textBoxInputOp1.KeyUp += (s, e) => {
                    if (e.Key == Key.Enter) {
                        foreach (var item in _dataGridOperations.Columns) {
                            if ((string)item.Header == "ИД"               ||
                                (string)item.Header == "Фамилия клиента"  ||
                                (string)item.Header == "Имя клиента"      ||
                                (string)item.Header == "Отчество клиента" ||
                                (string)item.Header == "Паспорт клиента"  ||
                                (string)item.Header == "Скидка (%)"       ||
                                (string)item.Header == "Фото клиента")
                                item.Visibility = Visibility.Visible;
                            else item.Visibility = Visibility.Collapsed;
                        } // foreach

                        // Непосредственно вычисление
                        _dataGridOperations.ItemsSource = _db.sp_Request04(_textBoxInputOp1.Text).AsParallel().ToList();

                        // Показываем таблицу
                        _dataGridOperations.Visibility = Visibility.Visible;

                        // Убираем подсказку и ввод. Если пользователь захочет ввести значения ещё раз - клик по меню
                        _notifiOp.Visibility = Visibility.Hidden;
                        _textBoxInputOp1.Visibility = Visibility.Hidden;

                        StatusText = "Запрос 04 успешно выполнен";
                    } // if
                };
            } catch (Exception) {
                StatusText = "Ошибка... Повторите ввод...";
            } // try-catch
        } // Request04

        // Запрос 05
        // Выбирает из таблиц КЛИЕНТЫ, ДОГОВОРЫ и АГЕНТЫ информацию обо всех договорах 
        // (ФИО клиента, Вид страхования, Сумма страхования, Дата заключения договора, ФИО агента), 
        // заключенных в некоторый заданный период времени о жилищном страховании.
        // Нижняя и верхняя границы периода задаются при выполнении запроса(в разработанном приложении)
        private void Request05(object obj)
        {
            // Скрываем таблицу
            _dataGridOperations.Visibility = Visibility.Collapsed;

            // Скрываем все столбцы, чтобы не мешались при вводе
            foreach (var item in _dataGridOperations.Columns) {
                item.Visibility = Visibility.Hidden;
            } // foreach

            // Подсказка
            _notifiOp.Visibility = Visibility.Visible;
            _notifiOp.Text = "Договора о жилищном страховании заключённые в период времени:";

            // Активируем ввод
            _textBoxInputOp1.Text = "";
            _textBoxInputOp2.Text = "";
            _textBoxInputOp1.SelectedText = "Дата от";
            _textBoxInputOp2.SelectedText = "Дата до";
            _textBoxInputOp1.Visibility = Visibility.Visible;
            _textBoxInputOp1.Focus();
            _textBoxInputOp2.Visibility = Visibility.Visible;
            StatusText = "ENTER - чтобы подтвердить ввод";

            try {
                // Событие для ввода значений по клавише Enter во вкладке операций
                // И уже моя стандартная низкоуровневая оптимизация...
                _textBoxInputOp2.KeyUp += (s, e) => {
                    ServiceRequest05(s, e);
                };
                _textBoxInputOp1.KeyUp += (s, e) => {
                    ServiceRequest05(s, e);
                };
            } catch (Exception) {
                StatusText = "Ошибка... Повторите ввод...";
            } // try-catch
        } // Request05
        private void ServiceRequest05(object s, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) {
                foreach (var item in _dataGridOperations.Columns) {
                    if ((string)item.Header == "Ф.И.О. клиента"           ||
                        (string)item.Header == "Сумма страхования"        ||
                        (string)item.Header == "Дата заключения договора" ||
                        (string)item.Header == "Ф.И.О. агента")
                        item.Visibility = Visibility.Visible;
                    else item.Visibility = Visibility.Collapsed;
                } // foreach

                // Парсим дату
                DateTime.TryParse(_textBoxInputOp1.Text, out DateTime dt1);
                DateTime.TryParse(_textBoxInputOp2.Text, out DateTime dt2);

                // Непосредственно вычисление 
                _dataGridOperations.ItemsSource = _db.sp_Request05(dt1, dt2).AsParallel().ToList();

                // Показываем таблицу
                _dataGridOperations.Visibility = Visibility.Visible;

                // Убираем подсказку и ввод. Если пользователь захочет ввести значения ещё раз - клик по меню
                _notifiOp.Visibility = Visibility.Hidden;
                _textBoxInputOp1.Visibility = Visibility.Hidden;
                _textBoxInputOp2.Visibility = Visibility.Hidden;

                StatusText = "Запрос 05 успешно выполнен";
            } // if
        } // ServiceRequest05

        // Запрос 06
        // Вычисляет для каждого договора размер комиссионного вознаграждения агента. 
        // Включает поля 
        // Дата заключения договора, 
        // Фамилия агента,
        // Имя агента,
        // Отчество агента,
        // Сумма страхования,
        // Комиссионные.Сортировка по полю Дата заключения договора
        // SumInsurance* (Tariff - Discount) = страховая премия
        private void Request06(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "Дата заключения договора" ||
                    (string)item.Header == "Фамилия агента"           ||
                    (string)item.Header == "Имя агента"               ||
                    (string)item.Header == "Отчество агента"          ||
                    (string)item.Header == "Сумма страхования"        ||
                    (string)item.Header == "Комиссионные")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request06().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            _dataGridOperations.VerticalScrollBarVisibility = ScrollBarVisibility.Visible;
            StatusText = "Запрос 06 успешно выполнен";
        } // Request06

        // Запрос 07
        // Выполняет группировку по полю Код агента в таблице ДОГОВОРЫ. 
        // Для каждой группы вычисляет максимальное и минимальное значение суммы страхования
        private void Request07(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "Максимальная сумма страхования" ||
                    (string)item.Header == "Минимальная сумма страхования"  ||
                    (string)item.Header == "Количество сумм")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request07().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 07 успешно выполнен";
        } // Request07

        // Запрос 08
        // Выполняет группировку по полю Дата заключения договора для договоров страхования автомобиля. 
        // Для каждой группы вычисляет среднее значения по полю Сумма страхования
        private void Request08(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "Средняя сумма страхования")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request08().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 08 успешно выполнен";
        } // Request08

        // Запрос 09
        // Создает таблицу НОВЫЕ_КЛИЕНТЫ, содержащую информацию о клиентах, для которых процент скидки равен нулю
        private void Request09(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "ИД"               ||
                    (string)item.Header == "Фамилия клиента"  ||
                    (string)item.Header == "Имя клиента"      ||
                    (string)item.Header == "Отчество клиента" ||
                    (string)item.Header == "Паспорт клиента"  ||
                    (string)item.Header == "Скидка (%)"       ||
                    (string)item.Header == "Фото клиента")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request09().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 09 успешно выполнен. Таблица НОВЫЕ_КЛИЕНТЫ создана, её содержимое в таблице операций";
        } // Request09

        // Запрос 10
        // Создает копию таблицы КЛИЕНТЫ с именем КОПИЯ_КЛИЕНТЫ
        private void Request10(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "ИД"               ||
                    (string)item.Header == "Фамилия клиента"  ||
                    (string)item.Header == "Имя клиента"      ||
                    (string)item.Header == "Отчество клиента" ||
                    (string)item.Header == "Паспорт клиента"  ||
                    (string)item.Header == "Скидка (%)"       ||
                    (string)item.Header == "Фото клиента")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request10().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 10 успешно выполнен. Копия таблицы КЛИЕНТЫ с именем КОПИЯ_КЛИЕНТЫ создана";
        } // Request10

        // Запрос 11
        // Удаляет из таблицы КОПИЯ_КЛИЕНТЫ записи, в которых значение в поле Процент скидки равен 0.5%
        private void Request11(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "ИД"               ||
                    (string)item.Header == "Фамилия клиента"  ||
                    (string)item.Header == "Имя клиента"      ||
                    (string)item.Header == "Отчество клиента" ||
                    (string)item.Header == "Паспорт клиента"  ||
                    (string)item.Header == "Скидка (%)"       ||
                    (string)item.Header == "Фото клиента")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request11().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 11 успешно выполнен. Из таблицы КОПИЯ_КЛИЕНТЫ удалены клиенты, у которых процент скидки равен 0.5%";
        } // Request11

        // Запрос 12
        // Устанавливает значение в поле Процент скидки в таблице 
        // КОПИЯ_КЛИЕНТЫ равным 0.5% для клиентов, имеющих процент скидки 0.4%
        private void Request12(object obj)
        {
            _textBoxInputOp1.Visibility = Visibility.Hidden;
            _textBoxInputOp2.Visibility = Visibility.Hidden;

            if (_notifiOp.Visibility == Visibility.Visible)
                _notifiOp.Visibility = Visibility.Hidden;

            foreach (var item in _dataGridOperations.Columns) {
                if ((string)item.Header == "ИД"               ||
                    (string)item.Header == "Фамилия клиента"  ||
                    (string)item.Header == "Имя клиента"      ||
                    (string)item.Header == "Отчество клиента" ||
                    (string)item.Header == "Паспорт клиента"  ||
                    (string)item.Header == "Скидка (%)"       ||
                    (string)item.Header == "Фото клиента")
                    item.Visibility = Visibility.Visible;
                else item.Visibility = Visibility.Collapsed;
            } // foreach

            _dataGridOperations.ItemsSource = _db.sp_Request12().AsParallel().ToList();

            _dataGridOperations.Visibility = Visibility.Visible;

            StatusText = "Запрос 12 успешно выполнен. В таблице КОПИЯ_КЛИЕНТЫ, где скидка была равна 0.4%, теперь скидка 0.5%";
        } // Request12
    } // class ApplicationViewModel
} // namespace InsuranceAgency
