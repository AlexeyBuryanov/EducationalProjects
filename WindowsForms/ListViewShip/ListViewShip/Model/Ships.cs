using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections;

namespace ListViewShip
{
    // Коллекция кораблей с обслуживающими методами
    [Serializable]
    public class Ships: IEnumerable
    {
        // Контейнер данных
        List<Ship> items = new List<Ship>();

        // Форматтер бинарной сериализации
        [NonSerialized]
        private BinaryFormatter bf;

        // Ссылка на элемент интерфейса главной формы
        public ListView ShipListView { get; set; }

        // "Проброс" свойства Count контейнера, на уровень класса Ships
        public int Count { get { return items.Count; } }


        // Индексатор для доступа к контейнеру
        public Ship this[int index]
        {
            get {
                CheckIndex(index);
                return items[index];
            } // get
            set {
                CheckIndex(index);

                // Сохранить Id при присваивании, т.е. существующий
                // идентификатор не изменяется, меняются только свойства
                value.Id = items[index].Id;
                items[index] = value;
            } // set
        } // indexer

        // Проверка индекса элемента массива
        private void CheckIndex(int index)
        {
            if (index < 0 || index >= items.Count)
                throw new IndexOutOfRangeException("Индекс за пределами коллекции кораблей");
        } // CheckIndex


        // Конструктор
        public Ships() { bf = new BinaryFormatter(); }


        // Добавление корабля в список
        public void Add(Ship ship)
        {
            // Сформировать уникальный ID в текущей коллекции
            int id = MakeUniqueId();
            ship.Id = id;
            items.Add(ship);
        } // Add

        // Формирование уникального Id в коллекции
        // Находим максимальный Id в коллекции, увеличиваем его на 1
        // реализация метода задания уникального идентификатора - автоинкремент
        // (стандарный способ работы с идентификатором в базах данных)
        private int MakeUniqueId()
        {
            int max = 0;
            foreach (var item in items)
                if (item.Id > max) max = item.Id;

            return max + 1;
        } // MakeUniqueId


        // Удалить элемент из списка по индексу
        public void RemoveAt(int index) { items.RemoveAt(index); } // Remove

        // Очистка контейнера данных
        public void Clear() { items.Clear(); } // Clear


        // Сериализация/запись данных в заданный файл - стандартная реализация
        public void Save(string fileName)
        {
            // Сериализация только контейнера данных - списка items 
            using (FileStream fs = new FileStream(fileName, FileMode.Create))
                bf.Serialize(fs, items);
        } // Save

        // Десериализация/чтение данных из заданного файла
        public void Load(string fileName)
        {
            // Восстанавливаем из файла только контейнер данных - списка items 
            using (FileStream fs = new FileStream(fileName, FileMode.Open))
                items = (List<Ship>)bf.Deserialize(fs);
        } // Load


        // Простейшая реализация интерфейса IEnumerable - берем 
        // перечислитель/итератор у контейнера хранения кораблей
        // IEnumerable разрешает работу foreach с нашим классом
        // Ну а наш класс просто будет транслировать запрос к итератору
        // в контейнер хранения. 
        // Т.е. фактически внешний мир связывается с реализацией итератора
        // нашего контейнера items
        public IEnumerator GetEnumerator() => items.GetEnumerator();
    } // class Ships
}
