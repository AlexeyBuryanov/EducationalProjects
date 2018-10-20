using System;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace HtmlDownloader
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Регулярное выражение для поиска тегов <img>
        private static readonly Regex ImgRegex = new Regex(@"\<img.+?src=\""(?<imgsrc>.+?)\"".+?\>",
           RegexOptions.ExplicitCapture | RegexOptions.Compiled);

        private readonly IDialogService _dialogService;
        private static string _fileData;

        public MainWindow()
        {
            InitializeComponent();

            _dialogService = new DefaultDialogService();

            textBoxMain.Text = "Программа позволяет скачать HTML-страницу по её адресу.\n" +
                "Страница сохраняется в определённую папку (диалог), после чего программа находит\n" +
                "на странице все картинки (regEx) и скачивает их в отдельную папку Images, " + 
                "которая находится рядом с html-файлом.";
        } // MainWindow


        // Открыть
        private void MenuMainOpen_Click(object sender, RoutedEventArgs e)
        {
            try {
                if (_dialogService.OpenFileDialog() == true) {
                    _fileData = File.ReadAllText(_dialogService.FilePath);
                    textBoxMain.Text = _fileData;
                    Status.Text = "Файл открыт";
                    MenuItemSave.IsEnabled = true;
                    MenuItemSaveAs.IsEnabled = true;
                } // if
            } catch (Exception ex) {
                _dialogService.ShowError(ex.Message);
                Status.Text = "Ошибка при открытии файла";
            } // try-catch
        } // MenuItemOpen_Click


        // Сохранить
        private void MenuMainSave_Click(object sender, RoutedEventArgs e)
        {
            try {
                if (!string.IsNullOrEmpty(_dialogService.FilePath)) {
                    File.WriteAllText(_dialogService.FilePath, _fileData);
                    Status.Text = "Сохранено";
                } else if (_dialogService.SaveFileDialog() == true) {
                    File.WriteAllText(_dialogService.FilePath, _fileData);
                    Status.Text = "Сохранено";
                } // if
            } catch (Exception ex) {
                _dialogService.ShowError(ex.Message);
                Status.Text = "Ошибка при сохранении файла";
            } // try-catch
        } // MenuItemSave_Click


        // Сохранить как
        private void MenuMainSaveAs_Click(object sender, RoutedEventArgs e)
        {
            try {
                if (_dialogService.SaveFileDialog() == true) {
                    File.WriteAllText(_dialogService.FilePath, _fileData);
                    Status.Text = $"Сохранено как: {_dialogService.FilePath}";
                } // if
            } catch (Exception ex) {
                _dialogService.ShowError(ex.Message);
                Status.Text = "Ошибка при сохранении файла";
            } // try-catch
        } // MenuItemSaveAs_Click


        // Выход
        private void MenuMainExit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        } // MenuItemExit_Click


        // Обработка по заданию
        private void ButtonSave_Click(object sender, RoutedEventArgs e)
        {
            progressBar.Value = 0;
            try {
                if (_dialogService.SaveFileDialog() == true) {
                    // Формируем веб-клиент
                    WebClient wc = new WebClient();
                    wc.DownloadFileAsync(new Uri(textBoxAddress.Text, UriKind.RelativeOrAbsolute), _dialogService.FilePath);
                    wc.DownloadFileCompleted += Wc_DownloadFileCompleted;
                    wc.DownloadProgressChanged += Wc_DownloadProgressChanged;

                    // Грузим изображения
                    DownloadingImages();
                } // if
            } catch (Exception ex) {
                _dialogService.ShowError(ex.Message);
                Status.Text = "Ошибка при сохранении веб-сайта";
            } // try-catch
        } // ButtonSave_Click

        private void Wc_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            progressBar.Value = e.ProgressPercentage;
        } // Wc_DownloadProgressChanged


        // Когда загрузка веб-сайта завершена
        private void Wc_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            // Читаем данные и отображаем
            _fileData = File.ReadAllText(_dialogService.FilePath);
            textBoxMain.Text = _fileData;

            Status.Text = $"Веб-страница сохранена как: {_dialogService.FilePath}";
        } // Wc_DownloadFileCompleted

        private void DownloadingImages()
        {
            string site = textBoxAddress.Text;
            string data;
            using (WebClient client = new WebClient()) {
                using (Stream stream = client.OpenRead(site)) {
                    using (StreamReader reader = new StreamReader(stream)) {
                        data = reader.ReadToEnd();
                    } // StreamReader
                } // Stream
            } // using

            // Создаём папку
            DirectoryInfo di = Directory.GetParent(_dialogService.FilePath);
            di = Directory.CreateDirectory(di.FullName + @"\Images");
            string _dirImages = di.FullName;

            ImgRegex.Matches(data)
                .Cast<Match>()
                // Данные из группы регулярного выражения
                .Select(m => m.Groups["imgsrc"].Value.Trim())
                // Удаляем повторы
                .Distinct()
                // Добавляем название сайта, если ссылки относительные
                .Select(url => url.Contains("http://") ? url : (site + url))
                // Получаем название изображения
                .Select(url => new { url, name = url.Split(new[] { '/' }).Last() })
                // Проверяем его
                .Where(arg => Regex.IsMatch(arg.name, @"[^\s\/]\.(jpg|png|gif|bmp)\z"))
                // Параллелим на 6 потоков
                .AsParallel()
                .WithDegreeOfParallelism(6)
                // Загружаем асинхронно
                .ForAll(value => {
                    string savePath = Path.Combine(_dirImages, value.name);
                    using (WebClient localClient = new WebClient()) {
                        localClient.DownloadFile(value.url, savePath);
                    } // WebClient
                }); // ForAll

            //// Ищем все вхождения любых ссылок
            //MatchCollection matches = Regex.Matches(_fileData, @"(https?:\/\/)?([\w\.]+)\.([a-z]{2,6}\.?)(\/[\w\.]*)*\/?");

            //StringBuilder sb = new StringBuilder();
            //// Ищем среди них картинки формата .png, .jpg
            //for (int i = 0; i < matches.Count; i++) {
            //    if (matches[i].Value.Contains(".jpg") || matches[i].Value.Contains(".png")) {
            //        // Формируем StringBuilder из уникальных ссылок
            //        if (!(sb.ToString().Contains(matches[i].ToString()))) {
            //            sb.Append(matches[i] + " ");
            //        } // if
            //    } // if
            //} // for

            //// Из StringBuilder'a создаём массив со всеми нужными нам ссылками на картинки 
            //string[] links = sb.ToString().Split(' ');

            //// Отдельный веб-клиент для загрузки изображений
            //WebClient wc = new WebClient();

            //// Перебираем ссылки и скачиваем в ранее созданную папку 
            //for (int i = 0; i < links.Length - 1; i++) {
            //    // Если ссылка не корректная и в ней нет http://
            //    if (!(links[i].Contains("//"))) {
            //        string link = "https://" + links[i];
            //        wc.DownloadFileAsync(new Uri(link, UriKind.RelativeOrAbsolute), _dirImages);
            //        wc.DownloadProgressChanged += Wc_DownloadImageProgressChanged;
            //    } else {
            //        wc.DownloadFileAsync(new Uri(links[i], UriKind.RelativeOrAbsolute), _dirImages);
            //        wc.DownloadProgressChanged += Wc_DownloadImageProgressChanged;
            //    } // if-else
            //} // for
        } // DownloadingImages
    } // MainWindow
} // RegExPractice
