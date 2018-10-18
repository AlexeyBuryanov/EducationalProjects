package Core.Threads;
import Core.Utils;
import Core.Word;
import java.io.*;
import java.util.*;

public class Task1SoloThread extends Thread
{
    public Task1SoloThread(String name)
    {
        super(name);
    } // Task1SoloThread


    public void run()
    {
        System.out.printf("Поток %s начал работу... \n", Thread.currentThread().getName());

        String folderName = "D:\\test";

        // Время начала работы потока
        long startWork = System.currentTimeMillis();

        File directory = new File(folderName);
        // Дабы юзер не ухитрился указать вместо папки путь к файлу
        if (directory.isDirectory()) {
            File[] files = directory.listFiles();
            // Убеждаемся, что файлы есть
            assert files != null;

            LinkedList<String> paths = new LinkedList<>();
            // Проходим по файлам в папке
            for (File file : files) {
                // Запоминаем путь к файлу для дальнейшей работы
                paths.add(file.getAbsolutePath());
            } // foreach files

            // * Основной список слов с которым будем работать
            LinkedList<Word> listWords = new LinkedList<>();

            for (String path : paths) {
                // Читатель
                FileReader fr = null;
                try {
                    fr = new FileReader(path);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } // try-catch

                // Буфер для чтения
                assert fr != null;
                BufferedReader r = new BufferedReader(fr);
                // Слова, которые будем сплитить
                String[] words;
                // Читаемая строка из файла
                String s;
                try {
                    while((s = r.readLine()) != null) {
                        words = s.split("[.,!?\":;\\s]");

                        for (String w : words) {
                            final boolean[] thereis = { false };

                            // Перебираем слова
                            // Если в списке есть такое слово (что прочитано)
                            // и это не какая-то пустота, то true
                            listWords.forEach(word -> {
                                if (Objects.equals(word.GetValue(), w) && !Objects.equals(w, "")) {
                                    thereis[0] = true;
                                } // if
                            });

                            // Добавляем в список, если там этого слова нет
                            if (!thereis[0]) {
                                listWords.add(new Word(1, w));

                                // Если слово есть, то теперь уже просто
                                // увеличиваем количество повторений (частотность)
                            } else {
                                listWords.forEach(word -> {
                                    if (Objects.equals(word.GetValue(), w)) {
                                        word.SetQuantityRepeats(word.GetQuantityRepeats()+1);
                                    } // if
                                });
                            } // if-else
                        } // foreach words

                        // Карта дерева (словарь)
                        Map<Integer, String> treeMap = new TreeMap<>(Collections.reverseOrder());
                        // Список уникальный слов, которые встречаются только 1 раз
                        LinkedList<Word> uniqueWords = new LinkedList<>();

                        // Основной список переносим в словарь т.к. там для нас "бесплатная" сортировка
                        listWords.forEach(word -> {
                            // Если в списке попадается слово с количеством повторения равным 1,
                            // то это уникальное слово и их может быть несколько. Их добавляем
                            // в отдельный список
                            if (word.GetQuantityRepeats() == 1) {
                                uniqueWords.add(word);
                            } else {
                                treeMap.put(word.GetQuantityRepeats(), word.GetValue());
                            } // if-else
                        });

                        // В итоге получаем словарь, который автоматом отсортирован по ключу
                        // и список со словами, которые встречаются единожды. Список выводим последним

                        Utils.WriteMapAndList(folderName + "\\FrequencyDictionary1.txt", treeMap, uniqueWords);
                    } // while

                    fr.close();
                    r.close();
                } catch (IOException e) {
                    e.printStackTrace();
                } // try-catch
            } // foreach paths
        } else {
            System.out.println("\nЭто файл, а не папка!\n");
        } // if-else

        System.out.printf("Поток %s закончил работу за %d миллисекунд.\n",
                Thread.currentThread().getName(), System.currentTimeMillis() - startWork);
    } // run
} // Task1SoloThread