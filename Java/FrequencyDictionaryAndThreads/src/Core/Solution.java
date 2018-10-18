package Core;
import Core.Threads.*;
import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

class Solution
{
    // Задание по умолчанию:
    //   Пользователь вводит имя папки с текстовыми файлами.
    //   Программа подсчитывает частотный словарь слов, встречаемых документах
    //   из данной папки. Слова из частотного словаря сохраняются в отдельном
    //   файле, отсортированные по частоте. Частота слова - это количество повторений
    //   слова.

    // 1. Задача решается 1 потоком и засекается время решения
    static void Task1()
    {
        try {
            System.out.println("Частотный словарь - решение одним потоком---------------------------------------");
            System.out.println("Главный поток начал работу...");

            Task1SoloThread solo = new Task1SoloThread("Task1");
            solo.start();

            try{
                solo.join();
            } catch(InterruptedException e) {
                System.out.printf("Поток %s был прерван...\n\n",
                        solo.getName());
                e.printStackTrace();
            } // try-catch

            System.out.println("Главный поток завершил работу.");
        } catch(Exception ex) {
            System.out.printf("\nОшибка в первой задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task1


    // 2. Задача решается 2 независимыми потоками, каждый имеет свою половину файлов для
    //    обработки и свой отдельный частотный словарь. Потоки работают независимо друг от друга
    //    и в конце работы частотные словари объединяются. Только тогда останавливаются часы времени работы
    static void Task2()
    {
        try {
            System.out.println("Частотный словарь - решение двумя потоками. У каждого своя половина-------------");
            System.out.println("Главный поток начал работу...");

            Map<Integer, String> map1 = new TreeMap<>(Collections.reverseOrder());
            LinkedList<Word> uniq1 = new LinkedList<>();
            Map<Integer, String> map2 = new TreeMap<>(Collections.reverseOrder());
            LinkedList<Word> uniq2 = new LinkedList<>();

            Task2Thread1 thread1 = new Task2Thread1("Task2Thread1", map1, uniq1);
            Task2Thread2 thread2 = new Task2Thread2("Task2Thread2", map2, uniq2);

            // Время начала выполнения задачи
            long startWork = System.currentTimeMillis();

            // Стартуем
            thread1.start();
            thread2.start();

            try {
                thread1.join();
                thread2.join();
            } catch(InterruptedException e) {
                System.out.printf("Один из потоков %s, %s был прерван...\n\n",
                        thread1.getName(), thread2.getName());
                e.printStackTrace();
            } // try-catch

            // Объединяем решение двух словарей в один
            Map<Integer, String> common = new TreeMap<>(Collections.reverseOrder());

            // Проходим по циклу в зависимости от размера словаря,
            // чтобы затронуть сравнение и добавление всех слов, что есть
            if (map1.size() > map2.size()) {
                for (Map.Entry<Integer, String> item : map1.entrySet()) {
                    // Если во втором дереве значение совпадает с первым деревом
                    // и при этом его нет в результате
                    if (map2.containsValue(item.getValue()) &&
                            !common.containsValue(item.getValue())) {
                        // Проходим по второму дерево
                        map2.forEach((key, value) -> {
                            // Если значения равные, то мы можем получить ключ (количество повторений)
                            // и суммировать их
                            if (Objects.equals(item.getValue(), value))
                                common.put(item.getKey()+key, item.getValue());
                        });
                    } else if (!common.containsValue(item.getValue())) {
                        common.put(item.getKey(), item.getValue());
                    } // if
                } // foreach
            } else {
                for (Map.Entry<Integer, String> item : map2.entrySet()) {
                    if (map1.containsValue(item.getValue()) &&
                            !common.containsValue(item.getValue())) {
                        map1.forEach((key, value) -> {
                            if (Objects.equals(item.getValue(), value))
                                common.put(item.getKey()+key, item.getValue());
                        });
                    } else if (!common.containsValue(item.getValue())) {
                        common.put(item.getKey(), item.getValue());
                    } // if
                } // foreach
            } // if

            uniq1.addAll(uniq2);
            Utils.WriteMapAndList("D:\\test\\FrequencyDictionary2.txt", common, uniq1);

            System.out.printf("Задача №2 решена за %d миллисекунд.\n",
                    System.currentTimeMillis() - startWork);
            System.out.println("Главный поток завершил работу.");
        } catch(Exception ex) {
            System.out.printf("\nОшибка во второй задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task2


    // 3. Задача решается 2 независимыми потоками, каждый имеет свою половину файлов для обработки
    //    и один общий частотный словарь, доступ к которому защищён критической секцией. Часы времени
    //    работы останавливаются, когда оба потока закончат свою работу
    static void Task3()
    {
        try {
            System.out.println("Частотный словарь - решение двумя потоками. Словарь общий-----------------------");
            System.out.println("Главный поток начал работу...");

            Task3CommonRes res = new Task3CommonRes(new TreeMap<>(Collections.reverseOrder()), new LinkedList<>());
            // Заглушка
            ReentrantLock locker = new ReentrantLock();

            Task3Thread1 thread1 = new Task3Thread1("Task3Thread1", res, locker);
            Task3Thread2 thread2 = new Task3Thread2("Task3Thread2", res, locker);

            // Время начала выполнения задачи
            long startWork = System.currentTimeMillis();

            // Стартуем
            thread1.start();
            thread2.start();

            try {
                thread1.join();
                thread2.join();
            } catch(InterruptedException e) {
                System.out.printf("Один из потоков %s, %s был прерван...\n\n",
                        thread1.getName(), thread2.getName());
                e.printStackTrace();
            } // try-catch

            // TODO: Избавляемся от одинаковых значений. Суммируем кол-во повторений
            /*Map<Integer, String> common = new TreeMap<>(Collections.reverseOrder());

            res.GetTreeMap().forEach((key, value) -> {

            });*/

            Utils.WriteMapAndList("D:\\test\\FrequencyDictionary3.txt", res.GetTreeMap(), res.GetUniqueWords());

            System.out.printf("Задача №3 решена за %d миллисекунд.\n",
                    System.currentTimeMillis() - startWork);
            System.out.println("Главный поток завершил работу.");
        } catch(Exception ex) {
            System.out.printf("\nОшибка в третьей задаче.\n%s\n\n%s\n\n",
                    ex.getMessage(), Arrays.toString(ex.getStackTrace()));
        } // try-catch
    } // Task2
} // Solution