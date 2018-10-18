package Core;
import Core.Tasks.Task1.Sorts.ChoiceSort;
import Core.Tasks.Task1.Sorts.MergeSort;
import Core.Tasks.Task1.Sorts.QuickSort;
import Core.Tasks.Task1.Vector;
import Core.Tasks.Task2.Threads.ThreadChoice;
import Core.Tasks.Task2.Threads.ThreadMerge;
import Core.Tasks.Task2.Threads.ThreadQuick;
import java.util.Arrays;

class Solution
{
    // 1. Реализовать паттерн «Стратегия» для класса Vector. Стратегия на примере сортировки вектора.
    //    3 стратегии сортировки. Класс вектор - отдельный пакет. Стратегии - отдельный пакет.
    //    Методы стратегий задаются интерфейсом.
    static void Task1()
    {
        try {
            System.out.println("StrategySort -------------------------------------------------------------------");
            Vector v = new Vector(new ChoiceSort());
            // Заполняем случайными числами
            for (int i = 0; i < 10; ++i) {
                v.PushBack(Utils.Random(1, 100));
            } // for

            System.out.println("New Vector:");
            v.Show();
            System.out.println("ChoiceSort:");
            v.Sort();
            v.Show();

            v = new Vector(new MergeSort());
            for (int i = 0; i < 10; ++i) {
                v.PushBack(Utils.Random(1, 100));
            } // for

            System.out.println("New Vector:");
            v.Show();
            System.out.println("MergeSort:");
            v.Sort();
            v.Show();

            v = new Vector(new QuickSort());
            for (int i = 0; i < 10; ++i) {
                v.PushBack(Utils.Random(1, 100));
            } // for

            System.out.println("New Vector:");
            v.Show();
            System.out.println("QuickSort:");
            v.Sort();
            v.Show();
        } catch(Exception ex) {
            System.out.printf("\nОшибка в первой задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task1


    // 2. Одновременно стартуют 3 потока, которые пытаются отсортировать 3 разных массива
    //    по 200000 случайных элементов. Используются разные алгоритмы сортировки и засекается
    //    время сортировки для каждого потока. Отсортированный массив сохраняется в файл.
    //    Времена сортировки выводятся на экран.
    static void Task2()
    {
        try {
            System.out.println("Threads ------------------------------------------------------------------------");
            System.out.println("Главный поток начал работу...");

            ThreadChoice tc = new ThreadChoice("ThreadChoice");
            ThreadMerge tm = new ThreadMerge("ThreadMerge");
            ThreadQuick tq = new ThreadQuick("ThreadQuick");

            tc.start();
            tm.start();
            tq.start();

            try{
                tc.join();
                tm.join();
                tq.join();
            } catch(InterruptedException e) {
                System.out.printf("Один из потоков (или все) %s, %s, %s был прерван прерван...\n\n",
                        tc.getName(), tm.getName(), tq.getName());
                e.printStackTrace();
            } // try-catch

            System.out.println("Главный поток завершил работу.");
        } catch(Exception ex) {
            System.out.printf("\nОшибка во второй задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task2
} // Solution