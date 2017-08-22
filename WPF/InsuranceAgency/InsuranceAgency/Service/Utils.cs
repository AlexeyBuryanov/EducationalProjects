using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media.Imaging;

namespace InsuranceAgency.Service
{
    public static class Utils
    {
        // Получает фото по заданому пути, возвращает массив байтов
        public static byte[] GetPhoto(string filePath)
        {
            FileStream stream = new FileStream(filePath, FileMode.Open, FileAccess.Read);
            BinaryReader reader = new BinaryReader(stream);

            byte[] photo = reader.ReadBytes((int)stream.Length);

            reader.Close();
            stream.Close();

            return photo;
        } // GetPhoto

        // Добавляет столбец в заданный DataGrid. Либо TextColumn, либо шаблонный столбец с картинкой
        public static void AddColumn(DataGrid dataGrid, string colHeader, double colWidth, string binding, 
            bool isReadOnly = false, bool isImage = false)
        {
            if (isImage) {
                FrameworkElementFactory factory = new FrameworkElementFactory(typeof(System.Windows.Controls.Image));
                Binding bind = new Binding(binding);
                factory.SetValue(System.Windows.Controls.Image.SourceProperty, bind);
                DataTemplate cellTemplate = new DataTemplate() { VisualTree = factory };
                DataGridTemplateColumn imgCol = new DataGridTemplateColumn() {
                    Header       = colHeader,
                    CellTemplate = cellTemplate,
                    Width        = colWidth,
                    IsReadOnly   = isReadOnly
                };
                dataGrid.Columns.Add(imgCol);
            } else { 
                dataGrid.Columns.Add(new DataGridTextColumn() {
                    Header     = colHeader,
                    Binding    = new Binding(binding),
                    Width      = colWidth,
                    IsReadOnly = isReadOnly
                });
            } // if
        } // AddColumn

        // TODO: Конвертирует bitmap в двоичное значение
        public static System.Data.Linq.Binary BitmapToBinary(BitmapImage bmp)
        {
            MemoryStream ms = new MemoryStream(bmp.StreamSource.ReadByte());
            System.Data.Linq.Binary bin = new System.Data.Linq.Binary(ms.ToArray());
            return bin;
        } // BitmapToBinary

        // Конвертирует массив байтов в BitmapImage
        public static BitmapImage ToBitmap(byte[] value)
        {
            if (value != null && value is byte[]) {
                byte[] ByteArray = value as byte[];
                BitmapImage bmp = new BitmapImage();
                bmp.BeginInit();
                bmp.StreamSource = new MemoryStream(ByteArray);
                bmp.EndInit();
                return bmp;
            } // if
            return null;
        } // ToBitmap

        // Конвертирует массив байтов в System.Drawing.Image
        public static System.Drawing.Image ByteArrayToImage(byte[] byteArrayIn)
        {
            using (MemoryStream ms = new MemoryStream(byteArrayIn)) {
                return System.Drawing.Image.FromStream(ms);
            } // using
        } // ByteArrayToImage
    } // class Utils
}
