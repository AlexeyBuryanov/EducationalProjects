package Core.Tasks.Task2.Threads;
import Core.Tasks.Task1.Sorts.MergeSort;
import Core.Utils;

public class ThreadMerge extends Thread
{
    public ThreadMerge(String name)
    {
        super(name);
    } // ThreadMerge


    public void run()
    {
        System.out.printf("Поток %s начал работу... \n", Thread.currentThread().getName());
        // Время начала работы потока
        long startWork = System.currentTimeMillis();

        int quantity = 200000;
        int[] array = new int[quantity];

        // Заполняем случайными числами
        Utils.FillArray(array, 1, quantity);

        // Сортируем
        new MergeSort().Sort(array);

        // Записываем в файл
        Utils.SaveArrayToTxt(array, "ThreadMerge.txt", 30);

        long result = System.currentTimeMillis() - startWork;
        System.out.printf("Поток %s закончил работу за %d миллисекунд.\n",
                Thread.currentThread().getName(), result);
    } // run
} // ThreadMerge