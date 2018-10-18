package Core.Tasks.Task1;

public class Vector
{
    private int[] _array;
    private ISortStrategy _sort;


    public Vector()
    {
        _array = new int[0];
    } // Vector
    public Vector(ISortStrategy strategy)
    {
        _array = new int[0];
        _sort = strategy;
    } // Vector


    public void Sort()
    {
        _sort.Sort(_array);
    } // Sort


    // Добавляет элемент в конец контейнера
    public void PushBack(int item)
    {
        // Временный массив
        int[] temp = new int[_array.length+1];
        // Копируем элементы уже созданного массива во временный
        for (int i = 0; i < temp.length; ++i) {
            // Дабы не выходить за пределы
            if (i == _array.length) break;
            temp[i] = _array[i];
        } // for i

        // Добавляем элемент в новый массив
        temp[_array.length] = item;

        // Копируем всё это дело в главный контейнер класса
        _array = new int[temp.length];
        System.arraycopy(temp, 0, _array, 0, temp.length);
    } // PushBack


    // Вывести вектор в консоль
    public void Show()
    {
        for (int item : _array) {
            System.out.printf("%d ", item);
        } // foreach
        System.out.println();
    } // Show
} // Vector