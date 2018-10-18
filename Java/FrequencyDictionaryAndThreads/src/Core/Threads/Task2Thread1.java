package Core.Threads;
import Core.Word;
import java.io.*;
import java.util.*;

public class Task2Thread1 extends Thread
{
    // Карта дерева (словарь)
    private Map<Integer, String> _treeMap;
    // Список уникальный слов, которые встречаются только 1 раз
    private LinkedList<Word> _uniqueWords;


    private Map<Integer, String> GetTreeMap()
    {
        return _treeMap;
    }
    private void SetTreeMap(Map<Integer, String> treeMap)
    {
        _treeMap = treeMap;
    }
    private LinkedList<Word> GetUniqueWords()
    {
        return _uniqueWords;
    }
    private void SetUniqueWords(LinkedList<Word> uniqueWords)
    {
        _uniqueWords = uniqueWords;
    }


    public Task2Thread1(String name, Map<Integer, String> treeMap, LinkedList<Word> uniqueWords)
    {
        super(name);
        SetTreeMap(treeMap);
        SetUniqueWords(uniqueWords);
    } // Task2Thread1


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
            // Если количество файлов чётное
            // нам нужна первая половина файлов
            if (files.length % 2 == 0) {
                // Проходим по первой половине
                for (int i = 0; i < files.length/2; ++i) {
                    // Запоминаем путь к файлу для дальнейшей работы
                    paths.add(files[i].getAbsolutePath());
                } // for i
                // Если нечётное, то вычитаем 1 и делим на 2.
                // Первый поток будет обрабатывать на 1 файл больше.
            } else {
                int length = (files.length-1)/2;
                for (int i = 0; i < length; ++i) {
                    paths.add(files[i].getAbsolutePath());
                } // for i
                // И последний файл, который не попадает под деление
                paths.add(files[length+1].getAbsolutePath());
            } // if

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

                        GetTreeMap().clear();
                        GetUniqueWords().clear();

                        // Основной список переносим в словарь т.к. там для нас "бесплатная" сортировка
                        listWords.forEach(word -> {
                            // Если в списке попадается слово с количеством повторения равным 1,
                            // то это уникальное слово и их может быть несколько. Их добавляем
                            // в отдельный список
                            if (word.GetQuantityRepeats() == 1) {
                                GetUniqueWords().add(word);
                            } else {
                                GetTreeMap().put(word.GetQuantityRepeats(), word.GetValue());
                            } // if-else
                        });
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
} // Task2Thread1